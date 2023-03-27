#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <transform.h>
#include <graphic.h>
#include <collision.h>

class GameObject2D
{
private:
    // Collision Box
    // Graphic

public:
    Graphic *graphic;
    Collider *collider;
    // Physics Info
    Transform2D *transform;
    Vec2 velocity = {0, 0};
    Vec2 force = {0, 0};
    float mass = 1;

    // functions
    void update();
    void draw();

    GameObject2D *setScale(Vec2 scale_)
    {
        transform->setScale(scale_);
        return this;
    }
    GameObject2D *setRotation(Vec2 rot_)
    {
        transform->setRotation(rot_);
        return this;
    }
    GameObject2D *setPosition(Vec2 pos_)
    {
        transform->setPosition(pos_);
        return this;
    }
    GameObject2D(/* args */);
    GameObject2D(Graphic *g);
    ~GameObject2D();
};

void GameObject2D::draw()
{
    graphic->draw(*transform);
}

void GameObject2D::update()
{
}

GameObject2D::GameObject2D(Graphic *g)
{
    graphic = g;
    collider = new SphereCollider();
    transform = new Transform2D();
}

GameObject2D::~GameObject2D()
{
    free(collider);
    free(graphic);
    free(transform);
}

#endif // !GAMEOBJECT_H