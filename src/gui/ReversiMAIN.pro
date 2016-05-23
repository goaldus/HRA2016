#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T22:05:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hra2016
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameui.cpp \
    ai.cpp \
    core.cpp \
    gameboard.cpp \
    save.cpp

HEADERS  += mainwindow.h \
    gameui.h \
    ai.h \
    core.h \
    gameboard.h \
    save.h

FORMS    += mainwindow.ui \
    gameui.ui
