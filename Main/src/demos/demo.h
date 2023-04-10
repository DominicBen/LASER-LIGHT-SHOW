#pragma once
#include <pointer.h>

class Demo
{
private:
    /* data */
public:
    Demo(/* args */){};
    float dt = 1;
    Pointer &p = Pointer::getInstance();
    int a = 0;
    int b = 0;
    int c = 0;
    ~Demo(){};
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    void setSpeed(float dt_) { dt = dt_; };
    void setA(int val) { a = val; };
    void setB(int val) { b = val; };
    void setC(int val) { c = val; };
    virtual void restart() = 0;
    virtual void init() = 0;
};

#include <demos/balls/ballsdemo.h>
#include <demos/grid/griddemo.h>
#include <demos/characters/charactersdemo.h>
#include <demos/sentences/sentencesdemo.h>
#include <demos/velocity/velocitydemo.h>
#include <demos/gravity/gravitydemo.h>
#include <demos/collision/collisiondemo.h>
#include <demos/beemovie/beemoviedemo.h>
#include <demos/ilda/cube3d/cube3dilda.h>