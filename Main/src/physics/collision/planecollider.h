#pragma once
#include <physics/collision/collider.h>
#include <physics/collision/collisionalgorithms.h>

struct CollisionPoints;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class PlaneCollider : public Collider
{
private:
    /* data */
public:
    Vec2 pos = {0, 0}; // offset in reference to parent object
    Vec2 normal{0, 1};
    float distance = 1000;

    CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, const Transform2D *colliderTransform) const override;

    CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, const Transform2D *colliderTransform) const override;

    CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, const Transform2D *colliderTransform) const override;

    PlaneCollider(){};
    PlaneCollider(Vec2 pos_, Vec2 normal_, float distance_) : pos(pos_), normal(normal_), distance(distance_){};
    ~PlaneCollider(){};
};