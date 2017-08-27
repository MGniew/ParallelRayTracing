#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include "qthread.h"
#include "scene.h"
#include "camera.h"
#include "raytracer.h"
#include "fileloader.h"
#include "qwaitcondition.h"


#include <mpi.h>
#include <stdio.h>

#include "global.h"
#include "queue"
#include "vector"



class MasterThread : public QThread
{
    Q_OBJECT

public:
    MasterThread(QObject *parent = 0);
    ~MasterThread();

signals:
    void workIsReady();

protected:
    void run() override;

    bool isAlive;
    QWaitCondition condition;
    Camera* camera;
    Scene* scene;
};

#endif // MASTERTHREAD_H
