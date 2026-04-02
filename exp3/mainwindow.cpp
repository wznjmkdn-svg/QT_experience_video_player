#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QSpinBox>
#include <QPainter>
#include <QDebug>  // 添加这行
#include <QMutexLocker>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_videoPlayer(new VideoPlayer(this))
{
    ui->setupUi(this);

    // 直接通过ui指针访问控件
    m_videoWidget = ui->widget;               // 视频显示区域

    m_seekSlider = ui->slider_progress;      // 进度条
    m_playPauseBtn = ui->But_play;       // 播放按钮
    m_timeLabel = ui->label_2;                // 时间标签
    m_openFileBtn = ui->actionOpenVideo;   // 文件路径输入框
    ui->fpsBox->setCurrentIndex(29);
//    m_videoWidget->setStyleSheet("background: #F0F0F0;");
//    m_videoWidget->setMinimumSize(650, 250);  // 16:9比例，比原640x180更合理
//    m_videoWidget->setSizePolicy(
//        QSizePolicy::Expanding,  // 水平方向尽可能扩展
//        QSizePolicy::Expanding   // 垂直方向尽可能扩展
//    );



//    m_videoDisplay->setAlignment(Qt::AlignCenter);
//    setCentralWidget(m_videoDisplay);

    // 视频播放器信号连接
    connect(m_videoPlayer, &VideoPlayer::frameReady,
            this, &MainWindow::slotUpdateVideoFrame,
            Qt::QueuedConnection);
    connect(m_videoPlayer, &VideoPlayer::durationChanged,
            this, &MainWindow::updateTimeDisplay);
    connect(m_videoPlayer, &VideoPlayer::positionChanged,
            this, [this](qint64 pos){
        if(!m_isManualSeeking) { // 仅在非手动操作时更新
            int percent = static_cast<int>((pos * 100.0) / m_duration);
            ui->slider_progress->setValue(percent);
        }
    });
    // 播放控制连接（统一使用UI控件)
    connect(ui->But_play, &QPushButton::clicked,
            this, &MainWindow::onPlayPauseClicked);
    connect(ui->slider_progress, &QSlider::sliderMoved,
            this, &MainWindow::onSeekSliderMoved);

    // 文件操作连接
    connect(ui->actionOpenVideo, &QPushButton::clicked,
            this, &MainWindow::onOpenFileClicked);
    connect(ui->lineEdit_filepath, &QLineEdit::editingFinished,
            this, &MainWindow::onOpenFileClicked);
    // 进度显示连接
    connect(ui->slider_progress, &QSlider::valueChanged,
            [this](int value) {
        if (m_duration > 0) {
            // 直接显示百分比值（范围0-100）
            ui->slider_value->setText(QString::number(value) + "%");

        }
    });
    // 修改信号连接
    connect(ui->slider_progress, &QSlider::sliderPressed, [this](){
        m_isManualSeeking = true;
    });
    connect(ui->slider_progress, &QSlider::sliderReleased, [this](){
        m_isManualSeeking = false;
        onSeekSliderMoved(ui->slider_progress->value());
    });


    // 帧率控制连接（需确保fpsBox已正确初始化）
    connect(ui->fpsBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
        if(index >= 0 && index < ui->fpsBox->count()) {
            bool ok;
            int fps = ui->fpsBox->currentText().split("fps")[0].toInt(&ok);
            if(ok) m_videoPlayer->setFrameRate(fps);
            else qWarning() << "Invalid frame rate data";
        }
            });
}





MainWindow::~MainWindow()
{
    delete ui;
    if(m_videoPlayer) {
        m_videoPlayer->stopPlayback();
        m_videoPlayer->deleteLater();

    }
    delete m_videoWidget;
}
// 工具函数：缩放图像并返回居中坐标
QPoint MainWindow::drawCenteredImage(QPainter &painter, const QImage &image, const QRect &targetRect) {
    if (image.isNull()) return QPoint();

    QImage scaled = image.scaled(targetRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPoint centerPos(
        targetRect.x() + (targetRect.width() - scaled.width()) / 2,
        targetRect.y() + (targetRect.height() - scaled.height()) / 2
    );
    painter.drawImage(centerPos, scaled);
    return centerPos;
}
void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);


    // 绘制黑底背景
   // painter.fillRect(m_videoWidget->rect(), Qt::black);



    // 统一绘制主窗口背景
    //painter.fillRect(rect(), Qt::black);

    // 仅在需要时绘制视频帧
    if (!m_currentFrame.isNull()) {
        drawCenteredImage(painter, m_currentFrame, m_videoWidget->geometry());
    }

}

// 更新视频帧显示
void MainWindow::drawImageFrame(QPainter& painter, QWidget* widget, QImage& img) {
    //painter.setBrush(Qt::black);
    if (!img.isNull()) {
         drawCenteredImage(painter, img, widget->geometry());
     }
}

void MainWindow::slotUpdateVideoFrame(const QImage &frame)
{
    QMutexLocker locker(& m_BufferMutex);
    m_currentFrame = frame.copy();  // 缓存最新帧
    QMetaObject::invokeMethod(this, [this](){
        m_videoWidget->update();
    }, Qt::QueuedConnection);

    // 保留进度更新逻辑
    qint64 currentMs = m_videoPlayer->currentPosition();
    m_seekSlider->setValue(currentMs);
    updateTimeDisplay(currentMs);
    // 更新进度显示
    if(m_duration > 0) {
        int percent = static_cast<int>((currentMs * 100.0) / m_duration);
        m_seekSlider->setValue(qBound(0, percent, 100));
    }

    //qDebug() << "帧数据接收成功，尺寸:" << frame.size(); // 添加调试输出
}

// 打开文件操作
void MainWindow::onOpenFileClicked()
{
    QString path = QFileDialog::getOpenFileName(this,
        "打开视频文件",
        QDir::homePath());
        //"视频文件 (*.264 *.265 *.mp4*hevc*.bin)");

    if(!path.isEmpty()) {
        if(m_videoPlayer->openFile(path)) {
            ui->lineEdit_filepath->setText(path); // 显示到U
            m_FilePath=path;
            m_duration = m_videoPlayer->totalDuration(); //调用VideoPlayer类的totalDuration()方法获取视频总时长（毫秒）
//            m_seekSlider->setRange(0, m_duration);//初始化QSlider的数值范围为0到视频总时长
            m_seekSlider->setRange(0, 100); // 设置百分比范围
            m_seekSlider->setValue(0);
            updateTimeDisplay(0);//初始化显示"00:00 / 总时长"格式的时间标签
            ui->slider_progress->setValue(0); // 重置进度条
            updateTimeDisplay(0);
            m_timeLabel->repaint(); // 立即重绘时间标签
        } else {
            QMessageBox::critical(this, "错误", "无法打开视频文件");
        }
    }
}

// 播放控制
void MainWindow::onPlayPauseClicked()
{
    if(m_videoPlayer->isPlaying()) { // 检查当前播放状态
        m_videoPlayer->pausePlayback(); // 暂停播放
        m_playPauseBtn->setText("▶");
    } else {
        m_videoPlayer->startPlayback();// 开始播放
        m_playPauseBtn->setText("⏸");
    }
}

// 进度条跳转
void MainWindow::onSeekSliderMoved(int position)
{
    if(!m_videoPlayer->isSeekable() || m_duration <= 0) return;

     // 将百分比转换为实际时间
     qint64 targetMs = static_cast<qint64>(
         (position / 100.0) * m_duration
     );

     // 添加跳转边界保护
     targetMs = qBound(0LL, targetMs, m_duration);
     m_videoPlayer->seekTo(targetMs);
}

// 时间显示格式化:将毫秒时间戳格式化为分钟:秒的显示格式
void MainWindow::updateTimeDisplay(qint64 current)
{    // 当前时间格式化（毫秒→mm:ss）

//    QString currentTime = QDateTime::fromMSecsSinceEpoch(current)
//        .toString("mm:ss");
//    // 总时长格式化（秒→mm:ss）
//    QString totalTime = QDateTime::fromMSecsSinceEpoch(m_duration).toString("mm:ss");
//       // 组合显示"当前时间/总时长"
//   qDebug()<<m_duration;
//    qDebug()<<totalTime;
//    m_timeLabel->setText(QString("%1 / %2").arg(currentTime, totalTime));
    // 使用QTime处理时间跨度
    QTime currentTime = QTime(0,0).addMSecs(current);
    QTime totalTime = QTime(0,0).addMSecs(m_duration);

    // 动态格式选择（超过1小时显示小时）
    QString format = (totalTime.hour() > 0) ? "HH:mm:ss" : "mm:ss";

    m_timeLabel->setText(
        QString("%1 / %2")
            .arg(currentTime.toString(format))
            .arg(totalTime.toString(format))
    );
    // 转换为时间跨度（支持超过24小时）
//    // 当前时间转换
//    qint64 hours = current / 3600000;
//    qint64 minutes = (current % 3600000) / 60000;
//    qint64 seconds = (current % 60000) / 1000;

//    // 总时长转换
//    qint64 totalHours = m_duration / 3600000;
//    qint64 totalMinutes = (m_duration % 3600000) / 60000;
//    qint64 totalSeconds = (m_duration % 60000) / 1000;

//    // 格式化为 hh:mm;ss
//    QString currentTime = QString("%1:%2;%3")
//        .arg(hours, 2, 10, QLatin1Char('0'))    // 小时补零到2位
//        .arg(minutes, 2, 10, QLatin1Char('0'))   // 分钟补零到2位
//        .arg(seconds, 2, 10, QLatin1Char('0'));  // 秒补零到2位

//    QString totalTime = QString("%1:%2;%3")
//        .arg(totalHours, 2, 10, QLatin1Char('0'))
//        .arg(totalMinutes, 2, 10, QLatin1Char('0'))
//        .arg(totalSeconds, 2, 10, QLatin1Char('0'));

//    m_timeLabel->setText(QString("%1 / %2").arg(currentTime, totalTime));
}
// 窗口关闭事件处理
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_videoPlayer && m_videoPlayer->isPlaying()) {
        m_videoPlayer->stopPlayback();
    }
    QMainWindow::closeEvent(event);
}





void MainWindow::slotGetFrame(QImage img)
{
    mOrigImage = img;
    update();
}
