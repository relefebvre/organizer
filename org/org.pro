TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += qt

SOURCES += main.cpp \
    organizer.cpp \
    orgview.cpp \
    doublon.cpp \
    doublontree.cpp \
    doublonmodel.cpp \
    md5key.cpp

HEADERS += \
    organizer.h \
    orgview.h \
    doublon.h \
    doublontree.h \
    doublonmodel.h \
    md5key.h

INCLUDEPATH +=/usr/include /usr/include/qt4/QtSql

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system -ltomcrypt

QT += core
QT += sql

FORMS += \
    orgview.ui

