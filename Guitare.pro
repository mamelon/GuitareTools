#-------------------------------------------------
#
# Project created by QtCreator 2012-04-28T13:53:59
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

TARGET = Guitare
TEMPLATE = app


include(Controleurs/Controleurs.pri)
include(Modeles/Modeles.pri)
include(CustomWidget/CustomWidget.pri)
include(Tools/Tools.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    ressources.qrc


LIBS += -lsndfile -lopenal

OBJECTS_DIR = .cmp/ojb
MOC_DIR = .cmp/moc
RCC_DIR = .cmp/rcc
UI_DIR = .cmp/ui
