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
    image.cpp \
    plugins/pluginsconfigdialog.cpp \
    plugins/pluginloader.cpp \
    plugins/pcpluginwidget.cpp \
    splashscreen.cpp \
    translation.cpp \
    aboutdialog.cpp \
    process.cpp \
    imageprocessor.cpp

HEADERS  += mainwindow.h \
    lenna.h \
    image.h \
    splashscreen.h \
    plugins/pluginsconfigdialog.h \
    plugins/inputplugin.h \
    plugins/outputplugin.h \
    plugins/pluginloader.h \
    plugins/plugin.h \
    plugins/pcpluginwidget.h \
    plugins/editplugin.h \
    translation.h \
    aboutdialog.h \
    process.h \
    imageprocessor.h

FORMS    += mainwindow.ui \
    plugins/pluginsconfigdialog.ui \
    plugins/pcpluginwidget.ui \
    aboutdialog.ui

RESOURCES += \
    lenna.qrc

DESTDIR     = ../

LIBS += -lopencv_core246
