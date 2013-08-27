TEMPLATE = lib
CONFIG += qt plugin
TARGET          = filechooser
QT              += core widgets gui
INCLUDEPATH	+= ../../lenna

HEADERS         = filechooser.h \
    widget.h \
    ../../lenna/image.h
SOURCES         = filechooser.cpp \
    widget.cpp \
    ../../lenna/image.cpp
FORMS += \
    widget.ui
OTHER_FILES += \
    filechooser.json

TRANSLATIONS += ../../i18n/filechooser_de.ts \
                ../../i18n/filechooser_en.ts \
                ../../i18n/filechooser_fr.ts \
                ../../i18n/filechooser_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lopencv_core246
