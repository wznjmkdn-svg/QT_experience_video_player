#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QSlider>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include "videoplayer.h"
#include <QVBoxLayout>  // 垂直布局
#include <QHBoxLayout>  // 水平布局
#include <QMutex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPoint drawCenteredImage(QPainter &painter, const QImage &image, const QRect &targetRect);

protected:
    void closeEvent(QCloseEvent *event) override; // 窗口关闭事件处理
    void paintEvent(QPaintEvent *event) override;//绘图函数
//    void resizeEvent(QResizeEvent *event) override;

private slots:
    // 视频帧更新槽
    void slotUpdateVideoFrame(const QImage &frame);
    // 进度条拖动槽
    void onSeekSliderMoved(int position);
    // 播放控制槽
    void onPlayPauseClicked();
    // 文件打开槽
    void onOpenFileClicked();
    void slotGetFrame(QImage img);//图像更新槽函数
    void drawImageFrame(QPainter& painter, QWidget* widget, QImage& img);

private:
    // 初始化界面组件

    void updateTimeDisplay(qint64 current);

    Ui::MainWindow *ui;          // Qt Designer生成的UI对象
    VideoPlayer *m_videoPlayer;  // 视频解码核心模块

    // 主界面组件
//    QLabel *m_videoDisplay;       // 视频显示区域
    // 替换原有QLabel视频显示
    QWidget *m_videoWidget;        // 新增视频显示组件
    QImage m_currentFrame;          // 当前视频帧缓存
    QSlider *m_seekSlider;        // 进度拖动条
    QPushButton *m_playPauseBtn;  // 播放/暂停按钮
    QLabel *m_timeLabel;          // 时间显示标签
    QHBoxLayout* createControlBar();
    QImage mOrigImage;      // 原始图像
    QImage m_displayBuffer;  // 双缓冲机制
    QMutex m_BufferMutex;

    bool m_isSliderDragging = false;  // 进度条是否拖动标志
    bool m_isManualSeeking = false;

    // 新增文件打开按钮
    QPushButton *m_openFileBtn; // 视频打开按钮
    QString m_FilePath;         //视频路径



    // 状态管理
    bool m_isPlaying = false;     // 播放状态标志
    qint64 m_duration = 0;        // 视频总时长(ms)
};

#endif // MAINWINDOW_H
