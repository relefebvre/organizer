TEMPLATE = app

CONFIG += qt

SOURCES += main.cpp \
    organizer.cpp \
    orgview.cpp \
    doublon.cpp \
    doublontree.cpp \
    doublonmodel.cpp

HEADERS += \
    organizer.h \
    orgview.h \
    doublon.h \
    doublontree.h \
    doublonmodel.h

INCLUDEPATH +=/usr/include /usr/include/qt4/QtSql

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system -ltomcrypt

QT += core
QT += sql

FORMS += \
    orgview.ui

