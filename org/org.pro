TEMPLATE = app
CONFIG += console
CONFIG += qt

SOURCES += main.cpp \
    organizer.cpp \
    orgview.cpp \
    md5key.cpp \
    doublon.cpp \
    doublontree.cpp \
    doublonmodel.cpp

HEADERS += \
    organizer.h \
    orgview.h \
    md5key.h \
    doublon.h \
    doublontree.h \
    doublonmodel.h

INCLUDEPATH +=/usr/include /usr/include/qt4/QtSql

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system -ltomcrypt

QT += core
QT += sql

FORMS += \
    orgview.ui

