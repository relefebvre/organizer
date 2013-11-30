TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

HEADERS +=

INCLUDEPATH +=/usr/include

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system

QT += sql

