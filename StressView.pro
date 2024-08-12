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
    model/genericsensor.cpp \
    model/pointinfo.cpp

HEADERS += \
    model/genericsensor.h \
    model/pointinfo.h
