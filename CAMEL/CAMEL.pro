#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T15:39:11
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CAMEL
TEMPLATE = app

SOURCES += main.cpp\
        camel.cpp \
    guimatrix.cpp \


HEADERS  += camel.h \
    guimatrix.h \

FORMS    += camel.ui \

RESOURCES += camelrsc.qrc



