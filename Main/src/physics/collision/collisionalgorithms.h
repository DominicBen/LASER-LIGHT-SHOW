#pragma once
struct CollisionPoints;

#include <dataobjects/transform.h>
#include <physics/collision/spherecollider.h>
#include <physics/collision/planecollider.h>

namespace collisionalgorithms
{
    CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb);

    CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider *a, const Transform2D *ta, const PlaneCollider *b, const Transform2D *tb);

    CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb);
};