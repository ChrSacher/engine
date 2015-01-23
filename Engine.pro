TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Math/Matrix4D.cpp \
    Math/Vector4D.cpp \
	Math/Vector3D.cpp \
    System/Log.cpp \
    Math/Vector2D.cpp \
    Math/Matrix3D.cpp \
    Math/Matrix2D.cpp


HEADERS += \
    Math/Matrix4D.h \
    Math/Vector4D.h \
	Math/Vector3D.h \
    System/Log.h \
    Math/Vector2D.h \
    Math/Matrix3D.h \
    Math/Matrix2D.h

