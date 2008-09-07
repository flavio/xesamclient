include(../confapp.pri)

# default to console (individual programs can always override this if needed)
CONFIG += console
CONFIG -= app_bundle
QT -= gui

# In a real application, you use the install locations. We just do this
# so you can see the examples without needing to install first.
INCLUDEPATH += ../../src
LIBS += -L../../lib

# link
LIBS += -l$$XESAMQLIB_LIBNAME
