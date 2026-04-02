#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QImage>
#include <QMap>
#include <QThread>
#include <QMutexLocker>  // 某些版本可能需要单独包含

extern"C"{
#include"libswscale/swscale.h"
#include"libavcodec/avcodec.h"
#include"libavformat/avformat.h"
#include<libavdevice/avdevice.h>
#include"libavutil/opt.h"
#include"libavutil/parseutils.h"
#include"libavutil/samplefmt.h"
#include"libavutil/fifo.h"
#include"libavutil/intreadwrite.h"
#include"libavutil/dict.h"
#include"libavutil/mathematics.h"
#include"libavutil/pixdesc.h"
#include"libavutil/avstring.h"
#include"libavutil/imgutils.h"
#include"libavfilter/avfilter.h"
#include"libavutil/pixfmt.h"
//#include"mtvideo_dec.h"
}

class VideoPlayer : public QThread  {
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);
    ~VideoPlayer();

    // 核心接口
    bool openFile(const QString &path);    // 打开媒体文件
    void setPlayRate(double rate);          // 设置播放速率
    void seekTo(qint64 position);             // 跳转到指定位置(ms)
    void setFrameRate(int fps);            //设置帧率


    // 硬件加速支持
    enum DecoderType { Software, QSV, CUDA };
    void enableHardwareAccel(DecoderType type);


    qint64 currentPosition() const;
    qint64 totalDuration() const;
    bool isPlaying() const;
    bool isSeekable() const;
    void stopPlayback();
    void combineMultiSlice(AVPacket *pkt);
    void buildIFrameIndex();
    void setVideoFrame(const QImage &frame) ;


signals:
    void frameReady(const QImage &frame);  // 解码帧就绪信号
    void durationChanged(qint64 durationMs);  // 总时长变化信号
    void errorOccurred(const QString &msg); // 错误通知
    void positionChanged(qint64 position); // 新增信号声明

public slots:
    void startPlayback();  // 开始播放
    void pausePlayback();   // 暂停播放
protected:
    void run() override;  // 添加override关键字


private:
    // FFmpeg核心结构体
    AVFormatContext *m_formatCtx = nullptr;
    AVCodecContext  *m_codecCtx = nullptr;
    AVFrame         *m_frame = nullptr;
    SwsContext      *m_swsCtx = nullptr;

    int m_frameRate = 30; // 存储当前帧率
    // 状态管理
    bool m_isPlaying = false;
    double m_playRate = 1.0;
    int m_videoStreamIndex = -1;

    // 多Slice处理
    QByteArray m_sliceBuffer;      // 分片缓存
    bool isNewFrameStart(const uint8_t *data) const;

    // I帧索引
    QMap<int64_t, int64_t> m_iFrameMap; // <时间戳, 文件偏移量>
    qint64 m_playStartTime = 0; // 新增播放基准时间
    qint64 m_pausedPosition = 0; // 记录暂停时的位置
    QString m_FilePath;
    qint64 m_processedBytes = 0; // 记录已处理的字节数
    QMutex m_seekMutex; // 添加互斥锁成员变量

    // 硬件加速相关
    AVBufferRef *m_hwDeviceCtx = nullptr;
    DecoderType m_decoderType = Software;

    // 工具方法
    QImage convertYUVToRGB(AVFrame *frame); // YUV转RGB
    void cleanupResources();       // 资源释放

};

#endif // VIDEOPLAYER_H
