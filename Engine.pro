TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
<<<<<<< HEAD
    Math/operators.cpp \
    Math/Matrix4D.cpp \
    Math/Vector4D.cpp \
    Math/Vector3D.cpp


HEADERS += \
    Math/operators.h \
    Math/Matrix4D.h \
    Math/Vector4D.h \
    Math/Vector3D.h
=======
    Math/Matrix4D.cpp \
    Math/Vector4D.cpp \
    System/Log.cpp


HEADERS += \
    Math/Matrix4D.h \
    Math/Vector4D.h \
    System/Log.h
>>>>>>> 5b8028165a2bb7a5b1b8145918f50de26fb774f3

