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
    view/addsensor.cpp \
    view/errorwindow.cpp \
    view/mainwindow.cpp \
    view/modifysensor.cpp \
    view/sensorinfowidget.cpp \
    view/sensorlistwidget.cpp \
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
    view/addsensor.h \
    view/errorwindow.h \
    view/mainwindow.h \
    view/modifysensor.h \
    view/sensorinfowidget.h \
    view/sensorlistwidget.h \
    visitor/genericvisitor.h \
    visitor/visitor.h

FORMS += \
    view/addsensor.ui \
    view/errorwindow.ui \
    view/mainwindow.ui \
    view/modifysensor.ui \
    view/sensorinfowidget.ui \
    view/sensorlistwidget.ui
