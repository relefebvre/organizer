TEMPLATE = app
CONFIG += console
CONFIG += qt

SOURCES += main.cpp \
    organizer.cpp

HEADERS += \
    organizer.h

INCLUDEPATH +=/usr/include /usr/include/qt4/QtSql

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system -ltomcrypt

QT += core
QT += sql

