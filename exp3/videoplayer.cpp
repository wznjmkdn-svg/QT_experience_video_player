#include "videoplayer.h"
#include <QDebug>
#include <QMutexLocker>  // 某些版本可能需要单独包含

#include <QFileInfo>
extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/time.h>
}

VideoPlayer::VideoPlayer(QObject *parent) : QThread(parent)
{
    avformat_network_init();
    //av_register_all();
}

VideoPlayer::~VideoPlayer()
{
    stopPlayback();
    if(m_formatCtx) avformat_close_input(&m_formatCtx);
    if(m_codecCtx) avcodec_free_context(&m_codecCtx);
    if(m_swsCtx) sws_freeContext(m_swsCtx);
}

void VideoPlayer::setFrameRate(int fps) {
    m_frameRate = qBound(1, fps, 30); // 限制帧率范围1-30
    //qDebug() << "帧率已设置为:" << m_frameRate;
}
bool VideoPlayer::openFile(const QString &path)
{
    stopPlayback();
    // 强制释放旧上下文
    // 强制重置所有时间相关变量
    m_pausedPosition = 0;
    m_playStartTime = 0;
    m_processedBytes = 0; // 新增：重置已处理字节数
    if(m_formatCtx) {
        avformat_close_input(&m_formatCtx);  // 新增
        m_formatCtx = nullptr;               // 新增
    }
    // 1. 打开媒体文件
    if(avformat_open_input(&m_formatCtx, path.toUtf8().constData(), nullptr, nullptr) != 0){
        qWarning() << "无法打开视频文件";
        return false;
    }
    m_FilePath=path;
    // 2. 获取流信息
    if(avformat_find_stream_info(m_formatCtx, nullptr) < 0){
        qWarning() << "无法获取流信息";
        return false;
    }

    // 3. 查找视频流
    m_videoStreamIndex = -1;
    for(uint i=0; i<m_formatCtx->nb_streams; i++){
        if(m_formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            m_videoStreamIndex = i;
            break;
        }
    }
    if(m_videoStreamIndex == -1){
        qWarning() << "未找到视频流";
        return false;
    }

    // 4. 初始化解码器
    AVCodecParameters *codecPar = m_formatCtx->streams[m_videoStreamIndex]->codecpar;
    const AVCodec *codec = nullptr;

    // 根据codec_id动态选择解码器
    if (codecPar->codec_id == AV_CODEC_ID_H264) {
        codec = avcodec_find_decoder_by_name("h264");
    } else if (codecPar->codec_id == AV_CODEC_ID_HEVC) {
        codec = avcodec_find_decoder_by_name("hevc");
    } else {
        qWarning() << "Unsupported codec";
        return false;
    }

    m_codecCtx = avcodec_alloc_context3(codec);
    if(avcodec_parameters_to_context(m_codecCtx, codecPar) < 0){
        qWarning() << "无法复制编解码器上下文";
        return false;
    }

    // 5. 打开解码器
    if(avcodec_open2(m_codecCtx, codec, nullptr) < 0){
        qWarning() << "无法打开解码器";
        return false;
    }

    // 初始化格式转换上下文(YUV->RGB)
    m_swsCtx = sws_getContext(
        m_codecCtx->width, m_codecCtx->height, m_codecCtx->pix_fmt,
        m_codecCtx->width, m_codecCtx->height, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );
    // 计算总时长（毫秒）
    qint64 durationMs = av_rescale_q(m_formatCtx->duration,
                                       AV_TIME_BASE_Q,
                                       {1, 1000}); // ✅ 正确转换单位
    emit durationChanged(durationMs); // 发送总时长(ms)
    emit currentPosition(); // 新增：立即发送时间归零信号
    return true;
}

void VideoPlayer::run()
{
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    uint8_t *rgbBuffer = (uint8_t*)av_malloc(
        av_image_get_buffer_size(AV_PIX_FMT_RGB24,
        m_codecCtx->width, m_codecCtx->height, 1)
    );

    while(!isInterruptionRequested()){
        // 新增播放状态检测
        if (!m_isPlaying) {
            QThread::msleep(10); // 降低CPU占用
            continue;
        }
        if(av_read_frame(m_formatCtx, &packet) < 0) break;

        if(packet.stream_index == m_videoStreamIndex){
            if(avcodec_send_packet(m_codecCtx, &packet) == 0){
                while(avcodec_receive_frame(m_codecCtx, frame) == 0){
                    if (packet.stream_index == m_videoStreamIndex) {
                         m_processedBytes += packet.size; // 累计视频流字节数
                     }
                    // YUV转RGB
                    uint8_t *dstData[1] = {rgbBuffer};
                    int dstLinesize[1] = {m_codecCtx->width * 3};
                    sws_scale(m_swsCtx, frame->data, frame->linesize,
                              0, m_codecCtx->height, dstData, dstLinesize);

                    // 生成QImage并发送信号
                    QImage img(rgbBuffer, m_codecCtx->width, m_codecCtx->height,
                              QImage::Format_RGB888);
                    emit frameReady(img.copy());
                    qint64 currentMs = currentPosition();
                    emit positionChanged(currentMs); // 触发信号
                    // 计算帧间隔时间
                    qint64 delay = static_cast<qint64>(1000.0 / m_frameRate * m_playRate);
                    QThread::msleep(delay);
                }
            }
        }
        av_packet_unref(&packet);
    }

    av_free(rgbBuffer);
    av_frame_free(&frame);
}


void VideoPlayer::seekTo(qint64 positionMs) {
    QMutexLocker locker(&m_seekMutex);

    // 清空解码缓冲区
    avcodec_flush_buffers(m_codecCtx);

    // 计算跳转时间基（参考网页3）
    AVStream* stream = m_formatCtx->streams[m_videoStreamIndex];
    int64_t timestamp = av_rescale_q(positionMs * 1000,
                                   AV_TIME_BASE_Q,
                                   stream->time_base);

    // 精准跳转（添加AVSEEK_FLAG_BACKWARD保证关键帧对齐）
    av_seek_frame(m_formatCtx, m_videoStreamIndex,
                timestamp, AVSEEK_FLAG_BACKWARD);

    // 通知界面更新（新增信号）
    emit positionChanged(positionMs);
}

// 获取当前播放位置
qint64 VideoPlayer::currentPosition() const {
    if (!m_formatCtx || m_videoStreamIndex < 0) return 0;

    // 获取文件总大小
    QFileInfo fileInfo(m_FilePath);
    const qint64 totalBytes = fileInfo.size();
    if (totalBytes <= 0) return 0;

    // 优先使用视频流码率（与totalDuration逻辑对齐）
    const int64_t bit_rate = (m_codecCtx->bit_rate > 0) ?
                           m_codecCtx->bit_rate :
                           m_formatCtx->bit_rate;

    // 计算当前时间（毫秒）
    if (bit_rate > 0) {
        return (m_processedBytes * 8 * 1000) / bit_rate;
    } else {
        // 降级使用文件比例估算
        const qint64 totalDurationMs = totalDuration();
        return (m_processedBytes * totalDurationMs) / totalBytes;
    };
}

// 获取总时长
qint64 VideoPlayer::totalDuration() const {
    if (!m_formatCtx || m_videoStreamIndex < 0) return 0;
//    qDebug()<<"*******************";
    AVStream *stream = m_formatCtx->streams[m_videoStreamIndex];
    AVRational time_base = stream->time_base;

    // 修复裸流异常时间基 (H.264默认1/90000)
    if (time_base.den > 1200000 || time_base.num != 1) {
        time_base = AVRational{1, 90000};
//        qDebug()<<"time_base.den > 1200000 || time_base.num != 1";
    }

    if (stream->duration == AV_NOPTS_VALUE) {
        // 通过实际文件大小获取
//       qDebug()<<"stream->duration == AV_NOPTS_VALUE";
        QFileInfo fileInfo(m_FilePath); // 需在openFile()中保存路径
        int64_t file_size = fileInfo.size();

        // 码率安全校验
        int64_t bit_rate = m_formatCtx->bit_rate > 0 ?
                          m_formatCtx->bit_rate :
                          1500 * 1024; // 1.5Mbps默认

        qint64 duration = (file_size * 8 * 1000) / bit_rate;

        // 异常结果过滤
        if (duration <= 0 || duration > 3600000 * 24) { // >24小时视为无效
            qWarning() << "估算时长异常，使用容器层数据";
            return av_rescale_q(m_formatCtx->duration,
                              AV_TIME_BASE_Q,
                              {1, 1000});
        }
        return duration;
    }
//    qDebug()<<"duration = av_rescale_q";
    qint64 duration = av_rescale_q(stream->duration, time_base, {1, 1000});

    // 最终校验
    if (duration < 0) {
//        qDebug()<<"duration < 0";
        return av_rescale_q(m_formatCtx->duration,
                          AV_TIME_BASE_Q,
                          {1, 1000});
    }
    return duration;
}
// 播放状态检查
bool VideoPlayer::isPlaying() const {
    return m_isPlaying;
}

// 可跳转状态判断
bool VideoPlayer::isSeekable() const {
    return m_formatCtx &&
        (m_formatCtx->iformat->flags & AVFMT_SEEK_TO_PTS);
}

// 停止播放实现
void VideoPlayer::stopPlayback() {
    if(isRunning()) {
        requestInterruption();
        wait();
        m_pausedPosition = 0;
        m_playStartTime = 0;
        m_processedBytes = 0; // 新增：停止时重置字节计数
    }
}

// videoplayer.cpp
void VideoPlayer::combineMultiSlice(AVPacket *pkt) {
    static QByteArray combinedData;
    const uint8_t startCode[] = {0x00, 0x00, 0x00, 0x01};

    // 检测新帧起始
    if (memcmp(pkt->data, startCode, 4) == 0) {
        uint8_t nalType = pkt->data[4] & 0x1F;
        if (nalType == 5 || nalType == 1) { // IDR或非IDR Slice
            if (!combinedData.isEmpty()) {
                // 发送已组合的帧数据
                AVPacket combinedPkt;
                av_new_packet(&combinedPkt, combinedData.size());
                memcpy(combinedPkt.data, combinedData.constData(), combinedData.size());
                avcodec_send_packet(m_codecCtx, &combinedPkt);
                av_packet_unref(&combinedPkt);
                combinedData.clear();
            }
        }
    }
    // 追加当前分片数据
    combinedData.append((const char*)pkt->data, pkt->size);
}

// videoplayer.cpp
void VideoPlayer::buildIFrameIndex() {
    m_iFrameMap.clear();
    int64_t filePos = 0;
    AVPacket pkt;  //
    av_init_packet(&pkt);  //
    const uint8_t startCode[] = {0x00, 0x00, 0x00, 0x01};  //


    // 遍历所有数据包
    while (av_read_frame(m_formatCtx, &pkt) >= 0) {
        if (pkt.stream_index == m_videoStreamIndex) {
            const uint8_t *data = pkt.data;
            int size = pkt.size;

            while (size > 4) {
                if (memcmp(data, startCode, 4) == 0) {
                    uint8_t nalType = data[4] & 0x1F;
                    if (nalType == 5) { // IDR帧
                        m_iFrameMap.insert(pkt.pts, filePos);
                    }
                }
                data += 4;
                size -= 4;
            }
        }
        filePos = pkt.pos;
        av_packet_unref(&pkt);
    }
    av_seek_frame(m_formatCtx, m_videoStreamIndex, 0, AVSEEK_FLAG_BACKWARD);
}
void VideoPlayer::startPlayback() {
    if (!isRunning()) {
        start();  // 继承自QThread的方法，启动线程执行run()
    }
    m_playStartTime = av_gettime_relative(); // 重置基准时间
    m_isPlaying = true;//设置成员变量m_isPlaying = true标记播放状态
}
void VideoPlayer::pausePlayback() {
    m_pausedPosition = currentPosition();
    m_isPlaying = false;
    // 注意：此处未停止线程，仅通过标志位控制run()内的解码逻辑
}
