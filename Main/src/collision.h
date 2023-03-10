#pragma once

#include <transform.h>
class Collision2D
{
private:
    /* data */
public:
    enum type
    {
        Sphere,
        Cube,
    };
    Transform2D transform;
    Transform2D *transform_of_root;
    Collision2D(Transform2D *transform_)
    {
        transform_of_root = transform_;
    }
    void update();
    ~Collision2D();
};

void Collision2D::update()
{
}
Collision2D::~Collision2D()
{
}
