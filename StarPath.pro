#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T19:49:22
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StarPath
TEMPLATE = app


SOURCES += main.cpp\
        starpath.cpp \
    celula.cpp \
    busca.cpp

HEADERS  += starpath.h \
    celula.h \
    busca.h

FORMS    += starpath.ui

RESOURCES += \
    files.qrc
