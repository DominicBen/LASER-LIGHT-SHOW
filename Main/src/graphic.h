#pragma once
#include <Arduino.h>

#include <pointer.h>
#include <transform.h>

class Graphic
{
private:
    /* data */
protected:
public:
    Pointer &p = Pointer::getInstance();
    Transform2D transform;
    virtual void draw() = 0;

    Graphic &setScale(Vec2 scale_)
    {
        transform.setScale(scale_);
        return *this;
    }
    Graphic &setRotation(Vec2 rot_)
    {
        transform.setRotation(rot_);
        return *this;
    }
    Graphic &setPosition(Vec2 pos_)
    {
        transform.setPosition(pos_);
        return *this;
    }
};
