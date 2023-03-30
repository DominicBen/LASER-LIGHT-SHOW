#pragma once
#include <collider.h>
#include <collisionalgorithms.h>

struct CollisionPoints;

class PlaneCollider : public Collider
{
private:
    /* data */
public:
    Vec2 pos;
    Vec2 normal;
    float distance;

    CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, Transform2D *colliderTransform) const override;

    CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, Transform2D *colliderTransform) const override;

    CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, Transform2D *colliderTransform) const override;

    PlaneCollider(/* args */){};
    ~PlaneCollider(){};
};