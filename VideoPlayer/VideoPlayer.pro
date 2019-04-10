#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T09:53:22
#
#-------------------------------------------------

QT       += core gui

TARGET = VideoPlayer
TEMPLATE = app
LIBS += -lvlc -lX11

SOURCES += main.cpp\
        mainwindow.cpp \
    vlcmedia.cpp

HEADERS  += mainwindow.h \
    vlcmedia.h

FORMS    += mainwindow.ui
