TEMPLATE = app
CONFIG += console
CONFIG += qt

SOURCES += main.cpp

HEADERS +=

INCLUDEPATH +=/usr/include /usr/include/qt4/QtSql

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system

QT += core
QT += sql

