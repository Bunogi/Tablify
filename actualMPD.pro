#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T15:48:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = actualMPD
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
				mainwindow.cpp

HEADERS  += mainwindow.h \
    arguments.h

FORMS    += mainwindow.ui
