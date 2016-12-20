#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T11:21:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeDemo
TEMPLATE = app


SOURCES += main.cpp\
        codedemo.cpp \
    myuiwgt.cpp \
    listviewdemo.cpp \
    dragwgt.cpp \
    appwgt_view.cpp \
    select_date_view.cpp

HEADERS  += codedemo.h \
    myuiwgt.h \
    listviewdemo.h \
    dragwgt.h \
    appwgt_view.h \
    select_date_view.h

FORMS    += codedemo.ui \
    myuiwgt.ui \
    listviewdemo.ui \
    dragwgt.ui
