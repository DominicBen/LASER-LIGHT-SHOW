#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <transform.h>
class GameObject2D
{
private:
    Transform2D transform;
    // Collision Box
    // Graphic
    // Physics Info
    // Gravity
    // Acceleration
    // Velocity

public:
    GameObject2D(/* args */);
    ~GameObject2D();
};

GameObject2D::GameObject2D(/* args */)
{
}

GameObject2D::~GameObject2D()
{
}

#endif // !GAMEOBJECT_H