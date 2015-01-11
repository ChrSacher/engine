TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Math/Matrix4D.cpp \
    Math/Vector4D.cpp \
    System/Log.cpp


HEADERS += \
    Math/Matrix4D.h \
    Math/Vector4D.h \
    System/Log.h

