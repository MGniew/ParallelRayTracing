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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    glwidget.cpp \
    scene.cpp \
    sphere.cpp \
    sceneobject.cpp \
    triangle.cpp \
    raytracer.cpp \
    light.cpp \
    camera.cpp \
    fileloader.cpp \
    masterthread.cpp \
    slavempi.cpp \
    pixels.cpp \
    serializable.cpp \
    statisticswindow.cpp \
    bsp.cpp \
    plane.cpp \
    boundingbox.cpp \
    inputparser.cpp

HEADERS += \
        mainwindow.h \
    glwidget.h \
    scene.h \
    sphere.h \
    sceneobject.h \
    triangle.h \
    raytracer.h \
    light.h \
    camera.h \
    vector3.h \
    fileloader.h \
    masterthread.h \
    slavempi.h \
    global.h \
    pixels.h \
    serializable.h \
    statisticswindow.h \
    bsp.h \
    plane.h \
    boundingbox.h \
    inputparser.h

FORMS += \
        mainwindow.ui \
    statisticswindow.ui

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
