#pragma once
class Demo
{
private:
    /* data */
public:
    Demo(/* args */){};
    float dt = 1;
    Pointer &p = Pointer::getInstance();
    ~Demo(){};
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    void setSpeed(float dt_) { dt = dt_; };
    virtual void restart() = 0;
    virtual void init() = 0;
};
