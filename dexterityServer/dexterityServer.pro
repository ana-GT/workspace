#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T15:36:02
#
#-------------------------------------------------

QT       += core gui bluetooth widgets

TARGET = dexterityServer
TEMPLATE = app


SOURCES += main.cpp\
        dexterityserver.cpp \
    server_unit.cpp

HEADERS  += dexterityserver.h \
    server_unit.h

FORMS    += dexterityserver.ui

CONFIG += mobility
MOBILITY = 

