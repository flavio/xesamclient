include(examples.pri)
!include( examples.pri ):message( "error including examples.pri" )
HEADERS = xesamtester.h
SOURCES += main.cpp \
    xesamtester.cpp
TARGET = example
