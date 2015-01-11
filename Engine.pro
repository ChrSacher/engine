TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Math/operators.cpp \
    Math/Matrix4D.cpp \
    Math/Vector4D.cpp


HEADERS += \
    Math/operators.h \
    Math/Matrix4D.h \
    Math/Vector4D.h

