#pragma once
#include <dataobjects/vec.h>
#include <functional>
#include <LCD/screenwrapper.h>

class Component
{
private:
    /* data */
public:
    virtual void draw() = 0;
    void draw(Vec2 pos_, Vec2 scale_)
    {
        pos = pos_;
        scale = scale_;
        draw();
    };
    virtual bool detectTouch(int x, int y) = 0;

    String text = "Default";

    Vec2 pos;
    Vec2 scale;

    virtual Component *setPos(Vec2 pos_)
    {
        pos = pos_;
        return this;
    }
    virtual Component *setScale(Vec2 scale_)
    {
        scale = scale_;
        return this;
    }
    Component(){};
    Component(String text_) : text(text_){};
    Component(Vec2 pos_, Vec2 scale_) : pos(pos_), scale(scale_){};
    ~Component(){};
};

#include <LCD/components/button.h>
#include <LCD/components/listcomponent.h>
#include <LCD/components/textcomponent.h>
#include <LCD/components/variablecomponent.h>