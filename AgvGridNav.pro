#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T11:45:43
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AgvGridNav
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    plotter.cpp \
    PGV100.cpp \
    ros_pgv100.cpp \
    Rs485.cpp \
    serial485.cpp \
    GraphSearch.cpp \
HEADERS  += mainwindow.h \
    plotter.h \
    Measure.h \
    PGV100.h \
    Rs485.h \
    cserial.h \
    serial485.h \
    GraphSearch.h \

FORMS    += mainwindow.ui
