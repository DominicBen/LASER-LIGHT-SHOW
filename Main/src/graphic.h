#pragma once
#include <pointer.h>
#include <transform.h>

class Pointer;

class Graphic
{
private:
    /* data */
protected:
public:
    Transform2D transform;
    virtual void draw(Pointer &p_);
};
