#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:10:00
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lenna
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lenna.cpp \
    splashscreen.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    lenna.h \
    splashscreen.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    lenna.qrc
