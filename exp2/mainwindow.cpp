#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include <QPainter>
#include <QFileDialog>

/*构造函数*/
label_original::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//创建ui页面

    mThread = new TransCodeThread;//创建类对象

    /*槽与信号链接*/
    connect(mThread,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));//进行图像传递和接收
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

    
    mThread->startPlay(filePath,width,height);//准备进行图像显示
        
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



/*打开原始文件的槽函数*/
void MainWindow::on_pushButton_open_1_clicked()
{

}

/*打开解码后文件的槽函数*/
void MainWindow::on_pushButton_open_2_clicked()
{

    
}
/*开始播放的槽函数*/
void MainWindow::on_pushButton_begin_clicked()
{
    
    
}
