/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QWidget *widget_video;
    QWidget *widget_video_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2_width;
    QLabel *label_3;
    QLineEdit *lineEdit_height;
    QPushButton *pushButton_display;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *fpsBox;
    QLabel *label;
    QLineEdit *lineEdit_filepath;
    QPushButton *pushButton_open;
    QScrollBar *playbackSlider;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_first;
    QPushButton *pushButton_display_2;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_finish;
    QPushButton *pushButton_save_photo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(572, 385);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_video = new QWidget(centralWidget);
        widget_video->setObjectName(QString::fromUtf8("widget_video"));

        gridLayout_2->addWidget(widget_video, 0, 0, 1, 1);

        widget_video_2 = new QWidget(centralWidget);
        widget_video_2->setObjectName(QString::fromUtf8("widget_video_2"));
        layoutWidget2 = new QWidget(widget_video_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 120, 481, 35));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(11);
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2_width = new QLineEdit(layoutWidget2);
        lineEdit_2_width->setObjectName(QString::fromUtf8("lineEdit_2_width"));

        horizontalLayout_2->addWidget(lineEdit_2_width);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_2->addWidget(label_3);

        lineEdit_height = new QLineEdit(layoutWidget2);
        lineEdit_height->setObjectName(QString::fromUtf8("lineEdit_height"));

        horizontalLayout_2->addWidget(lineEdit_height);

        pushButton_display = new QPushButton(layoutWidget2);
        pushButton_display->setObjectName(QString::fromUtf8("pushButton_display"));
        pushButton_display->setFont(font);

        horizontalLayout_2->addWidget(pushButton_display);

        layoutWidget = new QWidget(widget_video_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 70, 482, 35));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout->addWidget(label_4);

        fpsBox = new QComboBox(layoutWidget);
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->addItem(QString());
        fpsBox->setObjectName(QString::fromUtf8("fpsBox"));

        horizontalLayout->addWidget(fpsBox);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit_filepath = new QLineEdit(layoutWidget);
        lineEdit_filepath->setObjectName(QString::fromUtf8("lineEdit_filepath"));

        horizontalLayout->addWidget(lineEdit_filepath);

        pushButton_open = new QPushButton(layoutWidget);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));

        horizontalLayout->addWidget(pushButton_open);

        playbackSlider = new QScrollBar(widget_video_2);
        playbackSlider->setObjectName(QString::fromUtf8("playbackSlider"));
        playbackSlider->setGeometry(QRect(10, 50, 554, 14));
        playbackSlider->setOrientation(Qt::Horizontal);
        layoutWidget1 = new QWidget(widget_video_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 18, 426, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_first = new QPushButton(layoutWidget1);
        pushButton_first->setObjectName(QString::fromUtf8("pushButton_first"));
        pushButton_first->setFont(font);

        horizontalLayout_3->addWidget(pushButton_first);

        pushButton_display_2 = new QPushButton(layoutWidget1);
        pushButton_display_2->setObjectName(QString::fromUtf8("pushButton_display_2"));
        pushButton_display_2->setFont(font);

        horizontalLayout_3->addWidget(pushButton_display_2);

        pushButton_pause = new QPushButton(layoutWidget1);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));
        pushButton_pause->setFont(font);

        horizontalLayout_3->addWidget(pushButton_pause);

        pushButton_finish = new QPushButton(layoutWidget1);
        pushButton_finish->setObjectName(QString::fromUtf8("pushButton_finish"));
        pushButton_finish->setFont(font);

        horizontalLayout_3->addWidget(pushButton_finish);

        pushButton_save_photo = new QPushButton(widget_video_2);
        pushButton_save_photo->setObjectName(QString::fromUtf8("pushButton_save_photo"));
        pushButton_save_photo->setGeometry(QRect(450, 20, 101, 23));
        pushButton_save_photo->setFont(font);

        gridLayout_2->addWidget(widget_video_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 572, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\256\275", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\351\253\230", nullptr));
        pushButton_display->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\270\247\347\216\207", nullptr));
        fpsBox->setItemText(0, QCoreApplication::translate("MainWindow", "1fps", nullptr));
        fpsBox->setItemText(1, QCoreApplication::translate("MainWindow", "2fps", nullptr));
        fpsBox->setItemText(2, QCoreApplication::translate("MainWindow", "3fps", nullptr));
        fpsBox->setItemText(3, QCoreApplication::translate("MainWindow", "4fps", nullptr));
        fpsBox->setItemText(4, QCoreApplication::translate("MainWindow", "5fps", nullptr));
        fpsBox->setItemText(5, QCoreApplication::translate("MainWindow", "6fps", nullptr));
        fpsBox->setItemText(6, QCoreApplication::translate("MainWindow", "7fps", nullptr));
        fpsBox->setItemText(7, QCoreApplication::translate("MainWindow", "8fps", nullptr));
        fpsBox->setItemText(8, QCoreApplication::translate("MainWindow", "9fps", nullptr));
        fpsBox->setItemText(9, QCoreApplication::translate("MainWindow", "10fps", nullptr));
        fpsBox->setItemText(10, QCoreApplication::translate("MainWindow", "11fps", nullptr));
        fpsBox->setItemText(11, QCoreApplication::translate("MainWindow", "12fps", nullptr));
        fpsBox->setItemText(12, QCoreApplication::translate("MainWindow", "13fps", nullptr));
        fpsBox->setItemText(13, QCoreApplication::translate("MainWindow", "14fps", nullptr));
        fpsBox->setItemText(14, QCoreApplication::translate("MainWindow", "15fps", nullptr));
        fpsBox->setItemText(15, QCoreApplication::translate("MainWindow", "16fps", nullptr));
        fpsBox->setItemText(16, QCoreApplication::translate("MainWindow", "17fps", nullptr));
        fpsBox->setItemText(17, QCoreApplication::translate("MainWindow", "18fps", nullptr));
        fpsBox->setItemText(18, QCoreApplication::translate("MainWindow", "19fps", nullptr));
        fpsBox->setItemText(19, QCoreApplication::translate("MainWindow", "20fps", nullptr));
        fpsBox->setItemText(20, QCoreApplication::translate("MainWindow", "21fps", nullptr));
        fpsBox->setItemText(21, QCoreApplication::translate("MainWindow", "22fps", nullptr));
        fpsBox->setItemText(22, QCoreApplication::translate("MainWindow", "23fps", nullptr));
        fpsBox->setItemText(23, QCoreApplication::translate("MainWindow", "24fps", nullptr));
        fpsBox->setItemText(24, QCoreApplication::translate("MainWindow", "25fps", nullptr));
        fpsBox->setItemText(25, QCoreApplication::translate("MainWindow", "26fps", nullptr));
        fpsBox->setItemText(26, QCoreApplication::translate("MainWindow", "27fps", nullptr));
        fpsBox->setItemText(27, QCoreApplication::translate("MainWindow", "28fps", nullptr));
        fpsBox->setItemText(28, QCoreApplication::translate("MainWindow", "29fps", nullptr));
        fpsBox->setItemText(29, QCoreApplication::translate("MainWindow", "30fps", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        pushButton_open->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pushButton_first->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\207\263\345\274\200\345\247\213", nullptr));
        pushButton_display_2->setText(QCoreApplication::translate("MainWindow", "\347\273\247\347\273\255\346\222\255\346\224\276", nullptr));
        pushButton_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        pushButton_finish->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\207\263\347\273\223\346\235\237", nullptr));
        pushButton_save_photo->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
