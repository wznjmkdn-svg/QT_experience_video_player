#-------------------------------------------------
#
# Project created by QtCreator 2020-04-12T22:04:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSNR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        transcodethread.cpp

HEADERS  += mainwindow.h \
    globals.h \
    transcodethread.h

FORMS    += mainwindow.ui
