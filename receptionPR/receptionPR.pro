#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T15:58:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = receptionPR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialoglogin.cpp \
    boutonproducteur.cpp \
    boutonclient.cpp

HEADERS  += mainwindow.h \
    dialoglogin.h \
    boutonproducteur.h \
    boutonclient.h

FORMS    += mainwindow.ui \
    dialoglogin.ui
