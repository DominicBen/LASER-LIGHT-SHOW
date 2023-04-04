#pragma once
#include <vec.h>
#include <functional>
#include <screenwrapper.h>

class Component
{
private:
    /* data */
public:
    String text = "Default";

    Vec2 pos;
    Vec2 scale;

    virtual void draw() = 0;
    virtual void draw(Vec2 pos_, Vec2 scale_) = 0;
    virtual bool detectTouch(int x, int y) = 0;
    Component(){};
    Component(Vec2 pos_, Vec2 scale_) : pos(pos_), scale(scale_){};
    ~Component(){};
};
