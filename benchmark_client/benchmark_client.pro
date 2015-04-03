#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T14:51:00
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = benchmark_client
TEMPLATE = app


SOURCES += main.cpp\
        benchmark_client.cpp

HEADERS  += benchmark_client.h

FORMS    += benchmark_client.ui

CONFIG += mobility
MOBILITY = 

