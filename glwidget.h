#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <GL/glut.h>
#include "scene.h"
#include "camera.h"
#include "vector3.h"
#include "qpainter.h"
#include "masterthread.h"

class GLwidget : public QOpenGLWidget
{

    Q_OBJECT

public:
    GLwidget(QWidget *parent = 0);
    ~GLwidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    Camera* camera;
    Scene* scene;
    MasterThread masterThread;

private slots:
    void refresh();
};

#endif // GLWIDGET_H
