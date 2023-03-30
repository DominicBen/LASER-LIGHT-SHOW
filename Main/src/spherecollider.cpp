#include <spherecollider.h>
#include <collisionalgorithms.h>

CollisionPoints SphereCollider::testCollision(const Transform2D *transform, const Collider *collider, Transform2D *colliderTransform) const
{
    // Serial.println("testing collision");
    return collider->testCollision(colliderTransform, this, transform);
}
CollisionPoints SphereCollider::testCollision(const Transform2D *transform, const SphereCollider *sphere, Transform2D *colliderTransform) const
{
    // Serial.println("testing collision");
    return collisionalgorithms::FindSphereSphereCollisionPoints(this, transform, sphere, colliderTransform);
}
CollisionPoints SphereCollider::testCollision(const Transform2D *transform, const PlaneCollider *plane, Transform2D *colliderTransform) const
{
    // Serial.println("testing collision");
    return collisionalgorithms::FindSpherePlaneCollisionPoints(this, transform, plane, colliderTransform);
}

SphereCollider::SphereCollider(Vec2 *center_, float *radius_)
{
    center = center_;
    radius = radius_;
}