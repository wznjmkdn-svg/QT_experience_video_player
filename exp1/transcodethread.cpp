#include "transcodethread.h"
#include "globals.h"
#include <stdio.h>
#include <QElapsedTimer>
#include <QFile>  // 添加这行


QImage TransCodeThread::convertYUV420PToRGB(uchar *yuvData) {
    int width = mWidth;
    int height = mHeight;
    
    // YUV420P 数据格式：
    // - 前 `width*height` 字节：Y（亮度）
    // - 接下来的 `width*height/4` 字节：U（Cb色度）
    // - 最后的 `width*height/4` 字节：V（Cr色度）
    uchar *y = yuvData;
    uchar *u = y + width * height;
    uchar *v = u + (width * height) / 4;
    
    QImage img(width, height, QImage::Format_RGB32);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // 采样 UV（420P 每 2x2 像素共享 UV）
            int yVal = y[i * width + j];
            int uVal = u[(i/2) * (width/2) + (j/2)] - 128;
            int vVal = v[(i/2) * (width/2) + (j/2)] - 128;
            
            // YUV → RGB 转换公式（ITU-R BT.601 标准）
            int r = yVal + 1.402   * vVal;
            int g = yVal - 0.34414 * uVal - 0.71414 * vVal;
            int b = yVal + 1.772   * uVal;
            
            // 限制在 0~255 防止越界
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);
            
            img.setPixel(j, i, qRgb(r, g, b));
        }
    }
    return img;
}

TransCodeThread::TransCodeThread(QObject *parent)
    : QThread(parent)
{
}
void TransCodeThread::seekToFrame(int frame)
{
    if (!m_fileHandle) return;
    
    currentFrame = frame; // 更新全局变量
    m_seekPos = frame * m_frameSize; // 计算文件偏移（字节偏移 = 帧序号 * 每帧大小）
    // 判断是否超出范围
    if (m_seekPos >= m_fileSize) {
        m_seekPos = m_fileSize - m_frameSize; // 跳转到最后一帧
        currentFrame = (m_fileSize / m_frameSize) - 1;
    } else if (m_seekPos < 0) {
        m_seekPos = 0;
        currentFrame = 0;
    }
    m_seekRequested = true; // 触发跳转（run() 里会处理）
    //emit sig_FrameChanged(currentFrame); // 可选：通知 UI 更新
}


void TransCodeThread::startPlay(QString fileName, int width, int height, PixelFormat format) {
    mWidth = width;
    mHeight = height;
    m_pixelFormat = format;  // 保存当前格式

    // 计算帧大小（兼容 RGB32 和 YUV420P）
    switch (m_pixelFormat) {
    case RGB32:
        m_frameSize = width * height * 4;  // RGB32 = width*height*4
        break;
    case YUV420P:
        m_frameSize = width * height * 3 / 2;  // YUV420P = width*height*1.5
        break;
    }

    // 原有文件操作逻辑
    m_fileHandle = fopen(fileName.toUtf8().data(), "rb");
    if (m_fileHandle) {
        fseek(m_fileHandle, 0, SEEK_END);
        m_fileSize = ftell(m_fileHandle);
        fseek(m_fileHandle, 0, SEEK_SET);
        curTotalFrame = m_fileSize / m_frameSize; // 计算总帧数（全局变量）
        currentFrame = 0; // 重置当前帧
    }

    m_stopRequested = false;
    m_isPaused = false;
    start();  // 启动线程
}


void TransCodeThread::seekToStart()
{
    if (m_fileHandle) {
        m_seekPos = 0;
        m_seekRequested = true;
    }
}

void TransCodeThread::seekToEnd()
{
    if (m_fileHandle) {
        m_seekPos = m_fileSize - m_frameSize;
        if (m_seekPos < 0) m_seekPos = 0;
        m_seekRequested = true;
    }
}
void TransCodeThread::saveCurrentFrame(QString savePath, QString format) {
    if (!m_fileHandle) {
        qDebug("Error: File not open!");
        return;
    }

    // 读取当前帧原始数据
    long pos = ftell(m_fileHandle);
    uchar* frameData = new uchar[m_frameSize];
    fseek(m_fileHandle, pos, SEEK_SET);
    fread(frameData, 1, m_frameSize, m_fileHandle);

    // 按格式保存
    QFile file(savePath);
    if (file.open(QIODevice::WriteOnly)) {
        if (format == "yuv420p" || format == "rgb32") {
            // 原始数据直接写入（无转换）
            file.write((const char*)frameData, m_frameSize);
        } else {
            // 默认按BMP处理（需先转换为QImage）
            QImage img(frameData, mWidth, mHeight,
                      format == "rgb32" ? QImage::Format_RGB32 : QImage::Format_RGB888);
            img.save(&file, "BMP");
        }
        qDebug("Frame saved: %s (Format: %s)", qPrintable(savePath), qPrintable(format));
    }
    file.close();
    delete[] frameData;
}



void TransCodeThread::run() {
    uchar *frameBuffer = new uchar[m_frameSize];  // 统一缓冲区

    while (!m_stopRequested) {
        QElapsedTimer frameTimer;
        frameTimer.start();

        // 跳转处理（原功能保留）
        if (m_seekRequested) {
            fseek(m_fileHandle, m_seekPos, SEEK_SET);
            m_seekRequested = false;
        }
        currentFrame = (ftell(m_fileHandle) / m_frameSize);  //更新 currentFrame
        if (m_isPaused) {
            msleep(100);
            continue;
        }

        // 读取一帧
        int readSize = fread(frameBuffer, 1, m_frameSize, m_fileHandle);
        if (readSize <= 0) {
            emit sig_PlaybackFinished();
            break;
        }

        // 根据格式转换图像
        QImage img;
        switch (m_pixelFormat) {
        case RGB32:
            img = QImage(frameBuffer, mWidth, mHeight, QImage::Format_RGB32);
            break;
        case YUV420P:
            img = convertYUV420PToRGB(frameBuffer);  // 调用 YUV 转换
            break;
        }

        // 发送图像信号
        if (!img.isNull()) {
            emit sig_GetOneFrame(img);
        }

        // 原有 FPS 控制逻辑
        int remainingDelay = (1000 / fps) - frameTimer.elapsed();
        if (remainingDelay > 0) {
            msleep(remainingDelay);
        }
    }

    delete[] frameBuffer;
    if (m_fileHandle) {
        fclose(m_fileHandle);
        m_fileHandle = nullptr;
    }
}



// TransCodeThread::TransCodeThread(QObject *parent)
//     : QThread(parent)
// {
// }





void TransCodeThread::pause()
{
    m_isPaused = true;
}

void TransCodeThread::resume()
{
    m_isPaused = false;
}

void TransCodeThread::stop()
{
    m_stopRequested = true;
    if (isRunning()) {
        wait();
    }

    if (m_fileHandle) {
        fclose(m_fileHandle);
        m_fileHandle = nullptr;
    }
}






