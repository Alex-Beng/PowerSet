#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T13:31:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PowerSet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    setting.cpp

HEADERS  += mainwindow.h \
    setting.h

FORMS    += mainwindow.ui \
    setting.ui

RESOURCES += \
    src.qrc

DISTFILES +=
RC_ICONS = myico.ico
