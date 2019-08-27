#-------------------------------------------------
#
# Project created by QtCreator 2018-12-26T20:09:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maze020181226
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Matrix.cpp \
    my_queue.cpp \
    my_stack.cpp

HEADERS  += mainwindow.h \
    Matrix.h \
    my_queue.h \
    my_stack.h

FORMS    += mainwindow.ui

RESOURCES += \
    picture.qrc
