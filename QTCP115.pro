#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T09:44:53
#
#-------------------------------------------------

QT += charts
QT       += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTCP115
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database/netnumbers.cpp \
    Analysis/analysiscontrol.cpp \
    Analysis/analysisutils.cpp \
    database/dataall.cpp

HEADERS  += mainwindow.h \
    database/netnumbers.h \
    Analysis/analysiscontrol.h \
    Analysis/analysisutils.h \
    database/dataall.h

FORMS    += mainwindow.ui

RESOURCES += \
    myresources.qrc
