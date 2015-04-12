#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T16:47:35
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rfcomm_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include

CONFIG += mobility
MOBILITY = 

