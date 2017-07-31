#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <GL/glut.h>

class GLwidget : public QOpenGLWidget
{

public:
    GLwidget(QWidget *parent = 0);
    ~GLwidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // GLWIDGET_H
