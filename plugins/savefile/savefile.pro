TEMPLATE = lib
CONFIG += qt plugin
TARGET          = savefile
QT              += core widgets

INCLUDEPATH	+= ../../lenna
HEADERS         = savefile.h \
    widget.h \
    ../../lenna/image.h
SOURCES         = savefile.cpp \
    widget.cpp \
    ../../lenna/image.cpp
FORMS += \
    widget.ui
OTHER_FILES += \
    savefile.json

TRANSLATIONS += ../../i18n/savefile_de.ts \
                ../../i18n/savefile_en.ts \
                ../../i18n/savefile_fr.ts \
                ../../i18n/savefile_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lopencv_core246
