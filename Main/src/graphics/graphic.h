#pragma once
#include <Arduino.h>
#include <pointer.h>
#include <dataobjects/transform.h>

class Graphic
{
private:
    /* data */
protected:
public:
    enum Type
    {
        Circle,
        Rectangle,
        Triangle,
        Star,
        Polygon,
        Diamond,
        Grid,
        AlphaNumeric,
        Other,

    };

    Type type = Circle;
    Pointer &p = Pointer::getInstance();
    // Transform2D transform;
    virtual void draw(Transform2D transform, Color c) { Serial.println("Calling Basic Graphic Draw"); }
    virtual void update(){};
    // virtual Graphic *setScale(Vec2 scale_)
    // {
    //     transform.setScale(scale_);
    //     return this;
    // }
    // virtual Graphic *setRotation(Vec2 rot_)
    // {
    //     transform.setRotation(rot_);
    //     return this;
    // }
    // virtual Graphic *setPosition(Vec2 pos_)
    // {
    //     transform.setPosition(pos_);
    //     return this;
    // }
    Graphic(){};
    virtual ~Graphic(){};
};

#include <graphics/char.h>
#include <graphics/grid.h>
#include <graphics/sentence.h>
#include <graphics/shape.h>
#include <ILDA/ILDA.h>