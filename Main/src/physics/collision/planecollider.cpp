#include <physics/collision/planecollider.h>
CollisionPoints PlaneCollider::testCollision(const Transform2D *transform, const Collider *collider, const Transform2D *colliderTransform) const
{
    return collider->testCollision(colliderTransform, this, transform);
}
CollisionPoints PlaneCollider::testCollision(const Transform2D *transform, const SphereCollider *sphere, const Transform2D *colliderTransform) const
{
    return collisionalgorithms::FindPlaneSphereCollisionPoints(this, transform, sphere, colliderTransform);
}
CollisionPoints PlaneCollider::testCollision(const Transform2D *transform, const PlaneCollider *plane, const Transform2D *colliderTransform) const
{
    return {};
}