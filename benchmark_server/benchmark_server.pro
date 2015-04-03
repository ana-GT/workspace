#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T15:03:36
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = benchmark_server
TEMPLATE = app


SOURCES += main.cpp\
        benchmark_server.cpp \
    server_unit.cpp

HEADERS  += benchmark_server.h \
    server_unit.h

FORMS    += benchmark_server.ui

CONFIG += mobility
MOBILITY = 

