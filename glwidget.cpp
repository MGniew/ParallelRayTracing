#include "glwidget.h"

GLwidget::GLwidget(QWidget *parent) : QOpenGLWidget(parent)
{
setFixedSize(200, 200);
}

GLwidget::~GLwidget()
{
    delete scene;
    delete camera;
}

void GLwidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    camera = Camera::getInstance(new Vector3<float>(0.0, 0.0, -5.0),
                                         new Vector3<float>(0.0, 0.0, 1.0),
                                         new Vector3<float>(0.0, 1.0, 0.0),
                                         1.0,
                                         15.0,
                                         400,
                                         400,
                                         70.0);

    scene = Scene::getInstance();
    RayTracer rayTracer;

    rayTracer.basicRaytracer();
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
    float* pixel;
    pixel = new float[3];
    QPainter qPainter(this);

    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 400; j++) {
            pixel[0] = scene->getPixels()[i][j]->x;
            pixel[1] = scene->getPixels()[i][j]->y;
            pixel[2] = scene->getPixels()[i][j]->z;
            if (pixel[0] > 1) pixel[0]  = 1;
            if (pixel[1] > 1) pixel[1]  = 1;
            if (pixel[2] > 1) pixel[2]  = 1;
            qPainter.setPen(QColor(pixel[0]*255, pixel[1]*255, pixel[2]*255));
            qPainter.drawPoint(i, j);
       }
    }
    delete pixel;
    glFlush();
}
