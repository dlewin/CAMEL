#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T15:39:11
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CAMEL
TEMPLATE = app


SOURCES += main.cpp\
        camel.cpp \
    matrix.cpp \
    configurationmanager.cpp \
    sequencemanager.cpp \
    matrixtools.cpp \
    projectmatrix.cpp \
    guimatrix.cpp \
    pattern.cpp

HEADERS  += camel.h \
    matrix.h \
    configurationmanager.h \
    sequencemanager.h \
    matrixtools.h \
    projectmatrix.h \
    guimatrix.h \
    pattern.h

FORMS    += camel.ui
