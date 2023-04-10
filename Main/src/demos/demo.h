#pragma once
#include <pointer.h>
#include <gameobject.h>

class Demo
{
protected:
    /* data */
    float a = 0;
    float b = 0;
    float c = 0;

public:
    Demo(/* args */){};
    float dt = 1;
    bool mIsPaused = false;
    Pointer &p = Pointer::getInstance();
    ~Demo(){};
    // Media Control Playback
    void play() { mIsPaused = false; }
    void pause() { mIsPaused = true; }
    virtual void restart() = 0;
    // Drawing
    virtual void draw() = 0;
    virtual void update()
    {
        if (mIsPaused)
            return;
    };
    // Variables
    virtual void setA(float val) { a = val; };
    virtual void setB(float val) { b = val; };
    virtual void setC(float val) { c = val; };
    virtual float &getA() { return a; };
    virtual float &getB() { return b; };
    virtual float &getC() { return c; };
    virtual void init() = 0;
    void setSpeed(float dt_) { dt = dt_; };
};

#include <demos/balls/ballsdemo.h>
#include <demos/grid/griddemo.h>
#include <demos/characters/charactersdemo.h>
#include <demos/sentences/sentencesdemo.h>
#include <demos/velocity/velocitydemo.h>
#include <demos/gravity/gravitydemo.h>
#include <demos/collision/collisiondemo.h>
#include <demos/beemovie/beemoviedemo.h>
#include <demos/ilda/selection/selectilda.h>
#include <demos/games/pong.h>
#include <demos/ilda/badapple/badapple.h>