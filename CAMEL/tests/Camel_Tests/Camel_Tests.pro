#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T10:13:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Camel_Tests
TEMPLATE = app


SOURCES += ../../matrix.cpp main.cpp mainwindow.cpp


HEADERS += ../../matrix.h mainwindow.h

INCLUDEPATH += $$PWD/../../../../../googletest/googletest/msvc/gtest-md/Debug

DISTFILES += \
    gtest/internal/gtest-param-util-generated.h.pump \
    gtest/internal/gtest-type-util.h.pump

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../googletest/googletest/msvc/gtest-md/release/ -lgtestd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../googletest/googletest/msvc/gtest-md/debug/ -lgtestd
else:unix: LIBS += -L$$PWD/../../../../../googletest/googletest/msvc/gtest-md/ -lgtestd



DEPENDPATH += $$PWD/../../../../../googletest/googletest/msvc/gtest-md/Debug

#FORMS += mainwindow.ui
