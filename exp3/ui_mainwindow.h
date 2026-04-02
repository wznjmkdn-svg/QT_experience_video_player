/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_filepath;
    QPushButton *actionOpenVideo;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_width;
    QLabel *label_3;
    QLineEdit *lineEdit_height;
    QHBoxLayout *horizontalLayout_3;
    QSlider *slider_progress;
    QLineEdit *slider_value;
    QLabel *label_5;
    QComboBox *fpsBox;
    QPushButton *But_play;
    QWidget *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(698, 466);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 260, 551, 141));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_filepath = new QLineEdit(layoutWidget);
        lineEdit_filepath->setObjectName(QString::fromUtf8("lineEdit_filepath"));

        horizontalLayout->addWidget(lineEdit_filepath);

        actionOpenVideo = new QPushButton(layoutWidget);
        actionOpenVideo->setObjectName(QString::fromUtf8("actionOpenVideo"));

        horizontalLayout->addWidget(actionOpenVideo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_width = new QLineEdit(layoutWidget);
        lineEdit_width->setObjectName(QString::fromUtf8("lineEdit_width"));

        horizontalLayout_2->addWidget(lineEdit_width);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_height = new QLineEdit(layoutWidget);
        lineEdit_height->setObjectName(QString::fromUtf8("lineEdit_height"));

        horizontalLayout_2->addWidget(lineEdit_height);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        slider_progress = new QSlider(layoutWidget);
        slider_progress->setObjectName(QString::fromUtf8("slider_progress"));
        slider_progress->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(slider_progress);

        slider_value = new QLineEdit(layoutWidget);
        slider_value->setObjectName(QString::fromUtf8("slider_value"));
        slider_value->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(slider_value);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

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

        horizontalLayout_3->addWidget(fpsBox);

        But_play = new QPushButton(layoutWidget);
        But_play->setObjectName(QString::fromUtf8("But_play"));

        horizontalLayout_3->addWidget(But_play);


        verticalLayout->addLayout(horizontalLayout_3);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 50, 681, 211));
        widget->setStyleSheet(QString::fromUtf8("widget->setStyleSheet(\"background-color: black;\");"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 698, 23));
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
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\357\274\232", nullptr));
        actionOpenVideo->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\256\275\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\351\253\230\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\270\247\347\216\207\357\274\232", nullptr));
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

        But_play->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
