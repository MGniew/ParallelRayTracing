#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T20:01:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ParallelRayTracing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#OPT FLAG
QMAKE_CXXFLAGS_RELEASE *= -O3

INCLUDEPATH += $$PWD/Headers \
               $$PWD/Sources \
               $$PWD/Forms

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/glwidget.cpp \
    Sources/scene.cpp \
    Sources/sphere.cpp \
    Sources/sceneobject.cpp \
    Sources/triangle.cpp \
    Sources/raytracer.cpp \
    Sources/light.cpp \
    Sources/camera.cpp \
    Sources/fileloader.cpp \
    Sources/masterthread.cpp \
    Sources/slavempi.cpp \
    Sources/pixels.cpp \
    Sources/serializable.cpp \
    Sources/statisticswindow.cpp \
    Sources/bsp.cpp \
    Sources/plane.cpp \
    Sources/boundingbox.cpp \
    Sources/inputparser.cpp

HEADERS += \
    Headers/mainwindow.h \
    Headers/glwidget.h \
    Headers/scene.h \
    Headers/sphere.h \
    Headers/sceneobject.h \
    Headers/triangle.h \
    Headers/raytracer.h \
    Headers/light.h \
    Headers/camera.h \
    Headers/vector3.h \
    Headers/fileloader.h \
    Headers/masterthread.h \
    Headers/slavempi.h \
    Headers/global.h \
    Headers/pixels.h \
    Headers/serializable.h \
    Headers/statisticswindow.h \
    Headers/bsp.h \
    Headers/plane.h \
    Headers/boundingbox.h \
    Headers/inputparser.h

FORMS += \
    Forms\mainwindow.ui \
    Forms\statisticswindow.ui

LIBS += -lglut -lGLU

QMAKE_CXX = mpicxx
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = mpicc

#QMAKE_CFLAGS += $$system(mpicc -show)
#QMAKE_LFLAGS += $$system(mpicxx -show)
#QMAKE_CXXFLAGS += $$system(mpicxx -show) -DMPICH_IGNORE_CXX_SEEK
#QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx -show) -DMPICH_IGNORE_CXX_SEEK
