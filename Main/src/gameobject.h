#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <transform.h>
#include <physics.h>
#include <collision.h>
#include <graphic.h>
class GameObject2D
{
private:
    Transform2D transform;
    // Collision Box
    Collision2D colider = Collision2D(&transform);
    Physics2D phys = Physics2D(&transform);
    // Graphic
    Graphic *graphic;
    // Physics Info
    // Gravity
    // Acceleration
    // Velocity

public:
    void update();
    void draw();
    GameObject2D(/* args */);
    ~GameObject2D();
};

void GameObject2D::draw()
{
}

void GameObject2D::update()
{
    phys.update();
}

GameObject2D::GameObject2D(/* args */)
{
}

GameObject2D::~GameObject2D()
{
}

#endif // !GAMEOBJECT_H