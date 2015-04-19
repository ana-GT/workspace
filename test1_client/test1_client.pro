#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T12:23:21
#
#-------------------------------------------------

QT       += core gui widgets bluetooth

TARGET = test1_client
TEMPLATE = app


SOURCES += main.cpp\
        test1_client.cpp \
    client_unit.cpp \
    connectDialog.cpp

HEADERS  += test1_client.h \
    client_unit.h \
    connectDialog.h

FORMS    += test1_client.ui \
    connectDialog.ui

CONFIG += mobility
MOBILITY = 

