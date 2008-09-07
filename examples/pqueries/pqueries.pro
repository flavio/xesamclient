include(../examples.pri)
!include( ../examples.pri ):message( "error including examples.pri" )

HEADERS = searchtestjob.h \
    xesamtester.h
SOURCES += searchtestjob.cpp \
    main.cpp \
    xesamtester.cpp
TARGET = pqueries
