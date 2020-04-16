#-------------------------------------------------
#
# Project created by QtCreator 2020-03-03T23:43:11
#
#-------------------------------------------------

QT       += core gui
CONFIG += qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Optimization
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#MAKEFILE = $$PWD/../build/Makefile

INCLUDEPATH += $$PWD/../inc

SRC = $$PWD/../src
INC = $$PWD/../inc
UI = $$PWD/../uic
RSC = $$PWD/../res

DESTDIR = $$PWD/..

q# tutaj miały być ładnie poukładne foldery, ale szkoda mi już czasu dochodzić czemu qt mnie nie słuch
#DESTDIR = $$PWD/../build
#OBJECTS_DIR = $$PWD/../build/obj
#MOC_DIR = $$PWD/../build/moc
#RCC_DIR = $$PWD/../build/rcc
#UI_DIR = $$PWD/../build/ui

SOURCES += $$SRC/*.cpp

HEADERS += $$INC/*.h

FORMS += $$UI/*.ui

RESOURCES += $$RSC/*.qrc
