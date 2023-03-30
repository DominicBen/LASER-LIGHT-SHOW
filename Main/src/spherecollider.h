#pragma once
#include <collider.h>
struct CollisionPoints;
class Collider;

class SphereCollider : public Collider
{
private:
    /* data */
public:
    Vec2 *center;
    float *radius;
    CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, Transform2D *colliderTransform) const override;

    CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, Transform2D *colliderTransform) const override;

    CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, Transform2D *colliderTransform) const override;

    SphereCollider(Vec2 *center_, float *radius_);

    SphereCollider(){};
    ~SphereCollider(){};
};
