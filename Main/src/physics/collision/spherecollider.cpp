#include <physics/collision/spherecollider.h>
#include <physics/collision/collisionalgorithms.h>

CollisionPoints SphereCollider::testCollision(const Transform2D *transform, const Collider *collider, const Transform2D *colliderTransform) const
{
    // Serial.println("testing collision");
    return collider->testCollision(colliderTransform, this, transform);
}
CollisionPoints SphereCollider::testCollision(const Transform2D *transform, const SphereCollider *sphere, const Transform2D *colliderTransform) const
{
    // Serial.println("testing collision");
    return collisionalgorithms::FindSphereSphereCollisionPoints(this, transform, sphere, colliderTransform);
}
CollisionPoints SphereCollider::testCollision(const Transform2D *transform, const PlaneCollider *plane, const Transform2D *colliderTransform) const
{
    // Serial.println("testing collision");
    return collisionalgorithms::FindSpherePlaneCollisionPoints(this, transform, plane, colliderTransform);
}
