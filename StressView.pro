TEMPLATE = app
TARGET = StressView
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
    model/gpusensor.cpp \
    model/pointinfo/pointinfo.cpp \
    model/pointinfo/pointinfofloat.cpp \
    model/pointinfo/pointinfoint.cpp \
    model/ramsensor.cpp \
    model/sensorcontainer.cpp \
    view/mainwindow.cpp \
    visitor/genericvisitor.cpp \
    visitor/visitor.cpp

HEADERS += \
    model/cpusensor.h \
    model/genericsensor.h \
    model/gpusensor.h \
    model/pointinfo/pointinfo.h \
    model/pointinfo/pointinfofloat.h \
    model/pointinfo/pointinfoint.h \
    model/ramsensor.h \
    model/sensorcontainer.h \
    view/mainwindow.h \
    visitor/genericvisitor.h \
    visitor/visitor.h

FORMS += \
    view/mainwindow.ui
