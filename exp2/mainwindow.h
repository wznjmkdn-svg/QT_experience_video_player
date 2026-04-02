#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*头文件*/
#include <QMainWindow>
#include <QThread>
#include "transcodethread.h"


/*
 * 声明UI名字空间
 */
namespace Ui {
class MainWindow;
}

/*定义主窗口类*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:

    void paintEvent(QPaintEvent *event);//绘图函数

private:
    Ui::MainWindow *ui;                         //创建界面指针
    TransCodeThread *mThread;           //申明指向该类的指针
    QImage mImage;                           //记录当前的图像
    TransCodeThread *m_transcodeThread;
    

/*槽函数*/
private slots:
    void slotGetOneFrame(QImage img);//图像更新槽函数
    void on_pushButton_open_clicked();  //打开目录
    void on_pushButton_display_clicked();//开始播放
    void on_pushButton_first_clicked();
    void on_pushButton_display_2_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_finish_clicked();

    void on_pushButton_open_1_clicked();
    
    void on_pushButton_open_2_clicked();
    
    void on_pushButton_begin_clicked();
};
#endif // MAINWINDOW_H
