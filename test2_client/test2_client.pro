#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T12:23:21
#
#-------------------------------------------------

QT       += core gui widgets bluetooth

TARGET = test2_client
TEMPLATE = app


SOURCES += main.cpp\
        test2_client.cpp \
    client_unit.cpp \
    connectDialog.cpp \
    selectObjectDialog.cpp
HEADERS  += test2_client.h \
    client_unit.h \
    connectDialog.h \
    selectObjectDialog.h

FORMS    += test2_client.ui \
    connectDialog.ui \
    selectObjectDialog.ui

CONFIG += mobility
MOBILITY = 

