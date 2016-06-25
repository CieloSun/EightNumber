#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T10:13:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EightNumber
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    maze.h \
    thread.h

FORMS    += mainwindow.ui
