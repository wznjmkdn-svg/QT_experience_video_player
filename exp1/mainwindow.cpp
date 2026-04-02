#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include <QPainter>
#include <QFileDialog>

/*构造函数*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//创建ui页面

    mThread = new TransCodeThread;//创建类对象

    /*槽与信号链接*/
    connect(mThread,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));//进行图像传递和接收
    connect(ui->playbackSlider, &QSlider::sliderMoved, [this](int value) {
        mThread->seekToFrame(value); // 调用跳转
    });
    // // 在 MainWindow 构造函数里添加定时器
    // m_updateTimer = new QTimer(this);
    // connect(m_updateTimer, &QTimer::timeout, [this]() {
    //     ui->playbackSlider->setValue(currentFrame); // 更新进度条
    //     ui->lblCurFrame->setText(QString::number(currentFrame)); // 显示当前帧
    // });
    // m_updateTimer->start(50); // 50ms 更新一次（平滑显示）


}

/*析构函数*/
MainWindow::~MainWindow()
{
    delete ui;//删除ui界面
}

/*绘图显示函数*/
void MainWindow ::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(Qt::black);
    QRect rect = ui->widget_video->geometry();
    painter.drawRect(rect);

    if (mImage.size().width() <= 0) return;
        //将图像按比例缩放成和窗口一样大小
        QImage img = mImage.scaled(ui->widget_video->size(),Qt::KeepAspectRatio);
        int x = ui->widget_video->width() - img.width();
        int y = ui->widget_video->height() - img.height();
        x /= 2;
        y /= 2;
        x += ui->widget_video->x();
        y += ui->widget_video->y();
        painter.drawImage(QPoint(x,y),img); //画出图像
}

/*接收信号函数传递来过的图像，并准备执行绘画函数*/
void MainWindow::slotGetOneFrame(QImage img)
{
    mImage = img;
    update(); //调用update将执行 paintEvent函数
}

/*打开目录按键的槽函数*/
void MainWindow::on_pushButton_open_clicked()
{
    QString s = QFileDialog::getOpenFileName(   //获取.rgb文件字符串
        this, "选择RGB文件",
                "/",//初始目录
         "rgb文件 (*.*);;");
    if (!s.isEmpty())
    {
        s.replace("/","\\");
        ui->lineEdit_filepath->setText(s);//将字符串写入lineEdit_filepath文本框
    }
}

/*开始播放按键的槽函数*/
void MainWindow::on_pushButton_display_clicked()
{
    /*提取三个文本框的内容*/
    QString filePath = ui->lineEdit_filepath->text();
   //QString filePath = QFileDialog::getOpenFileName(this,
   //    "Open Video File",
   //    "",
   //    "YUV Files (*.yuv);;RGB Files (*.rgb);;All Files (*)");
    if (filePath.isEmpty()) return;
    // 自动检测格式
    TransCodeThread::PixelFormat format;
    if (filePath.endsWith(".yuv", Qt::CaseInsensitive)) {
        format = TransCodeThread::YUV420P;
    } else {
        format = TransCodeThread::RGB32;  // 默认 RGB
    }
    int width = ui->lineEdit_2_width->text().toInt();//toInt()表示将类型转化成int
    int height = ui->lineEdit_height->text().toInt();

    // if(ui->fpsBox->currentIndex()==0)//如果下拉框中的数值是25fps
    //     mThread->Setfps_25();
    // else//否则
    //     mThread->Setfps_30();
    // 假设您已经在ui中有一个QComboBox* fpsBox成员变量
// 并且在初始化时已经填充了1-30的选项

// 获取当前选择的FPS值
    int selectedFps = ui->fpsBox->currentText().split("fps")[0].toInt(); 

    // 根据选择的FPS值进行设置
    if(selectedFps >= 1 && selectedFps <= 30) {
        fps = selectedFps;
        
    } else {
        // 处理非法值的情况
        qWarning() << "Invalid FPS value selected:" << selectedFps;
        fps=30; // 设置一个默认值
    }

    
    mThread->startPlay(filePath, width, height, format);//准备进行图像显示
        
}

void MainWindow::on_pushButton_first_clicked()
{
    mThread->seekToStart();


}

void MainWindow::on_pushButton_display_2_clicked()
{
    mThread->resume();

}

void MainWindow::on_pushButton_pause_clicked()
{
    mThread->pause();

}


void MainWindow::on_pushButton_finish_clicked()
{
    mThread->seekToEnd();

}

void MainWindow::on_pushButton_save_photo_clicked()
{
    // 1. 获取用户选择的保存格式
    QString selectedFormat = "";
    // if (ui->radioRGB32->isChecked()) {
    //     selectedFormat = "rgb32";
    // } else if (ui->radioYUV420P->isChecked()) {
    //     selectedFormat = "yuv420p";
    // } else if (ui->radioBMP->isChecked()) {
    //     selectedFormat = "bmp";
    // }

    // 2. 生成默认文件名（视频文件名_帧号.扩展名）
    QString baseName = QFileInfo(ui->lineEdit_filepath->text()).baseName();
    QString defaultFileName = QString("%1_frame%2").arg(baseName).arg(currentFrame);
    QString filter = "";

    defaultFileName += ".rgb";
    filter = "RGB32 Raw Data (*.rgb)";
    // 3. 根据格式设置文件扩展名和过滤器
    // if (selectedFormat == "rgb32") {
    //     defaultFileName += ".rgb";
    //     filter = "RGB32 Raw Data (*.rgb)";
    // } 
    // else if (selectedFormat == "yuv420p") {
    //     defaultFileName += ".yuv";
    //     filter = "YUV420P Raw Data (*.yuv)";
    // }
    // else { // BMP
    //     defaultFileName += ".bmp";
    //     filter = "BMP Image (*.bmp)";
    // }

    // 4. 弹窗让用户确认保存路径
    QString savePath = QFileDialog::getSaveFileName(
        this,
        "保存当前帧",
        defaultFileName,
        filter
    );

    if (savePath.isEmpty()) return; // 用户取消

    // 5. 执行保存（分两种情况处理）
    if (selectedFormat == "bmp") {
        // 保存为BMP（从当前显示的QImage保存）
        if (!mImage.isNull()) {
            mImage.save(savePath, "BMP");
            qDebug() << "Frame saved as BMP:" << savePath;
        }
    } 
    else {
        // 保存原始数据（RGB32/YUV420P）
        mThread->saveCurrentFrame(savePath, selectedFormat);
    }
}




