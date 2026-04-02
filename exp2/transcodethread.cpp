#include "transcodethread.h"
#include "globals.h"
#include <stdio.h>
#include <QElapsedTimer>


TransCodeThread::TransCodeThread(QObject *parent)
    : QThread(parent)
{
}

void TransCodeThread::startPlay(QString infile, int width, int height)
{
    if (isRunning()) {
        stop();
    }

    mFilePath = infile;
    mWidth = width;
    mHeight = height;
    m_stopRequested = false;
    m_isPaused = false;
    m_seekRequested = false;
    
    m_frameSize = width * height * sizeof(RGB32);
    
    m_fileHandle = fopen(mFilePath.toUtf8().data(), "rb");
    if (m_fileHandle) {
        fseek(m_fileHandle, 0, SEEK_END);
        m_fileSize = ftell(m_fileHandle);
        fseek(m_fileHandle, 0, SEEK_SET);
    }

    if (!isRunning()) {
        start();
    }
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

void TransCodeThread::run() 
{
    QElapsedTimer frameTimer;
    BYTE *rgbBuffer = new BYTE[m_frameSize];
    if (!rgbBuffer || !m_fileHandle) {
        delete[] rgbBuffer;
        return;
    }

    while (!m_stopRequested) {
        frameTimer.restart();

        // 处理跳转请求
        if (m_seekRequested) {
            fseek(m_fileHandle, m_seekPos, SEEK_SET);
            m_seekRequested = false;
        }

        if (m_isPaused) {
            msleep(100);
            continue;
        }

        int readSize = fread(rgbBuffer, 1, m_frameSize, m_fileHandle);
        if (readSize <= 0) {
            if (feof(m_fileHandle)) {
                emit sig_PlaybackFinished();
                break;
            }
            break;
        }

        if (readSize == m_frameSize) {
            QImage tmpImg((uchar *)rgbBuffer, mWidth, mHeight, QImage::Format_RGB32);
            if (!tmpImg.isNull()) {
                emit sig_GetOneFrame(tmpImg.copy());
            }
        }

        int elapsed = frameTimer.elapsed();
        int remainingDelay = (1000 / fps) - elapsed;
        if (remainingDelay > 0) {
            msleep(remainingDelay);
        }
    }

    delete[] rgbBuffer;
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






