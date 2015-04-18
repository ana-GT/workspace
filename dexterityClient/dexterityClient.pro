#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T17:13:19
#
#-------------------------------------------------

QT       += core gui widgets bluetooth

TARGET = dexterityClient
TEMPLATE = app


SOURCES += main.cpp\
        dexterityclient.cpp \
    client_unit.cpp \
    connectDialog.cpp

HEADERS  += dexterityclient.h \
    client_unit.h \
    connectDialog.h

FORMS    += dexterityclient.ui \
    connectDialog.ui
