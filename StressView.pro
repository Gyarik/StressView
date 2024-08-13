TEMPLATE = app
TARGET = HazardView
INCLUDEPATH += .
CONFIG += c++17

QT += widgets
QT += core
QT += gui
QT += charts

SOURCES += \
    main.cpp \
    model/cpusensor.cpp \
    model/genericsensor.cpp \
    model/pointinfo.cpp

HEADERS += \
    model/cpusensor.h \
    model/genericsensor.h \
    model/pointinfo.h
