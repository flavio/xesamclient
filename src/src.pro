# #####################################################################
# Automatically generated by qmake (2.01a) Sat May 17 11:38:43 2008
# #####################################################################
XESAMQLIB_BASE = ..
XESAMQLIB_INCBASE = ../include
XESAMQLIB_SRCBASE = .
TEMPLATE = lib
TARGET = xesamqlib
DESTDIR = $$XESAMQLIB_BASE/lib
VERSION = 0.0.1
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += debug
QT += dbus
QT -= gui

# Input
PRIVATE_HEADERS = session_p.h \
    dbusinterface.h
PUBLIC_HEADERS = globals.h \
    query.h \
    search.h \
    session.h
HEADERS += $$PRIVATE_HEADERS \
    $$PUBLIC_HEADERS
SOURCES += session_p.cpp \
    dbusinterface.cpp \
    query.cpp \
    search.cpp \
    session.cpp
