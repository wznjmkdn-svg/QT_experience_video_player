#ifndef TRANSCODETHREAD_H
#define TRANSCODETHREAD_H

/*定义头文件*/
#include <QThread>
#include <QImage>
//#include <QTime>
#include <QElapsedTimer>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <atomic>

/*声明RBG32*/
typedef unsigned char BYTE;
typedef struct RGB32 {
  BYTE    rgbBlue;      // 蓝色分量
  BYTE    rgbGreen;     // 绿色分量
  BYTE    rgbRed;       // 红色分量
  BYTE    rgbReserved;  // 保留字节（用作Alpha通道或忽略）
} RGB32;

/*视频显示类声明，继承于QThread（线程）*/
class TransCodeThread : public QThread
{
    Q_OBJECT

public:
    enum PixelFormat { RGB32, YUV420P };  // 只保留两种格式
    void setPixelFormat(PixelFormat format);
    explicit TransCodeThread(QObject *parent = nullptr);
    ~TransCodeThread() {
        stop();
    };

    void startPlay(QString fileName, int width, int height, PixelFormat format = RGB32);
    PixelFormat currentFormat() const { return m_pixelFormat; }
    void Setfps_25();                                               //帧率
    void Setfps_30();

    void pause();
    void resume();
    void stop();
    void seekToStart();
    void seekToEnd();
    void seekToPercent(double percent);  // 按百分比跳转
    
    long getCurrentPosition() const;     // 获取当前播放位置
    long getTotalFrames() const;         // 获取总帧数
    void saveCurrentFrame(QString savePath, QString format); // 新增保存函数

public slots:
    void seekToFrame(int frame); // 进度条跳转时调用

signals:
    void sig_GetOneFrame(QImage image);

    //void sig_GetOneFrame(QImage); //获取到一帧图像 就发送此信号
    void sig_PlaybackFinished();
    void sig_PositionChanged(long position, long total); // 位置变化信号

private:
    PixelFormat m_pixelFormat;
    QImage convertYUV420PToRGB(uchar *yuvData);

    void run();//线程入口

    QString mFilePath;//文件地址
    int mWidth;             //视频宽度
    int mHeight;            //视频高度
    //QTime time;             //时间类
    QElapsedTimer timer;
    // int fps;                    //帧率;
    //bool m_stopRequested = false;

    //bool m_stopRequested = false;
    //bool m_isPaused = false;
    QMutex m_pauseMutex;
    QWaitCondition m_pauseCondition;
    FILE* m_fileHandle = nullptr;
    qint64 m_fileSize = 0;
    qint64 m_frameSize = 0;
    std::atomic<bool> m_stopRequested{false};
    std::atomic<bool> m_isPaused{false};
    QMutex m_fileMutex;
    bool m_seekRequested;  // 跳转请求标志
    long m_seekPos;        // 跳转目标位置
    long m_currentPos;      

};

#endif // TRANSCODETHREAD_H
