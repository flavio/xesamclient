include(examples.pri)
!include( examples.pri ):message( "error including examples.pri" )
HEADERS = XesamTester.h
SOURCES += main.cpp \
    XesamTester.cpp
TARGET = example
