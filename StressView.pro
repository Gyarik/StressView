TEMPLATE = app
TARGET = HazardView
INCLUDEPATH += .

QT += widgets
QT += core
QT += gui
QT += charts

SOURCES += \
    main.cpp \
    model/genericsensor.cpp

HEADERS += \
    model/genericsensor.h
