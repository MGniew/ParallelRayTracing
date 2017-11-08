#include "glwidget.h"

GLwidget::GLwidget(QWidget *parent) : QOpenGLWidget(parent)
{
setFixedSize(200, 200);
scene = Scene::getInstance();

camera = Camera::getInstance();

}

GLwidget::~GLwidget()
{

}

void GLwidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void GLwidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLwidget::paintGL()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter qPainter(this);
    int iMax = camera->getPixWidth();
    int jMax = camera->getPixHeight();

    QImage img((uchar *)scene->pixels->data, iMax, jMax, QImage::Format_RGB888);
    qPainter.drawImage(0,0,img);

    glFlush();
}
