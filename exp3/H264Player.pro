#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T14:42:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = H264Player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        videoplayer.cpp

HEADERS  += mainwindow.h \
    videoplayer.h

FORMS    += mainwindow.ui


FFMPEG_HOME=C:\ffmpeg-7.1.1-full_build-shared\ffmpeg-7.1.1-full_build-shared

#设置 ffmpeg 的头文件
INCLUDEPATH += $$FFMPEG_HOME/include

#设置导入库的目录一边程序可以找到导入库
# -L ：指定导入库的目录
# -l ：指定要导入的 库名称
LIBS +=  -L$$FFMPEG_HOME/lib \
         -lavcodec \
         -lavdevice \
         -lavfilter \
        -lavformat \
        -lavutil \
        -lpostproc \
        -lswresample \
        -lswscale

