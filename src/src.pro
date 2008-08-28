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
PRIVATE_HEADERS = XesamQSession_p.h \
    XesamQDBusInterface.h
PUBLIC_HEADERS = XesamQGlobals.h \
    XesamQQuery.h \
    XesamQSearch.h \
    XesamQSession.h \
    dbusoperators.h
HEADERS += $$PRIVATE_HEADERS \
    $$PUBLIC_HEADERS
SOURCES += dbusoperators.cpp \
    XesamQSession_p.cpp \
    XesamQDBusInterface.cpp \
    XesamQQuery.cpp \
    XesamQSearch.cpp \
    XesamQSession.cpp
