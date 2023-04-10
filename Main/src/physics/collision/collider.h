#pragma once

#include <dataobjects/transform.h>
class SphereCollider;
class PlaneCollider;
struct CollisionPoints
{
    Vec2 a;
    Vec2 b;
    Vec2 normal;
    float depth;
    bool hasCollision;
};

class Collider
{
private:
    /* data */
public:
    Collider(/* args */){};
    ~Collider(){};

    virtual CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, const Transform2D *colliderTransform) const = 0;
    virtual CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, const Transform2D *colliderTransform) const = 0;
    virtual CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, const Transform2D *colliderTransform) const = 0;
};