#-------------------------------------------------
#
# Project created by QtCreator 2020-12-10T10:21:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = publications
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    test.cpp \
    tag.cpp

HEADERS  += mainwindow.h \
    test.h \
    tag.h \
    methodes.h

FORMS    += mainwindow.ui \
    test.ui \
    tag.ui
