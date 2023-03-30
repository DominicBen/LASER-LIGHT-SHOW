#include <collisionalgorithms.h>
#include <planecollider.h>
CollisionPoints collisionalgorithms::FindSphereSphereCollisionPoints(const SphereCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb)
{
    CollisionPoints ret;
    Serial.println("Testing collision between two spheres?");
    float distance = Vec2::distance(ta->pos, tb->pos);
    Serial.println(distance);
    ret.depth = (ta->scale.x + tb->scale.x) - distance;
    Serial.println(ret.depth);
    if (ret.depth > 0)
    {
        ret.hasCollision = true;
        ret.normal = tb->pos - ta->pos;
        if (distance == 0)
        {
            ret.normal = {1, 0};
        }
        ret.normal.normalize();
        ret.a = ta->pos + ret.normal * (ta->scale.x - (distance - tb->scale.x) / 2.0f);
        ret.b = ret.a;
    }
    else
    {
        ret.hasCollision = false;
    }
    return ret;
}

CollisionPoints collisionalgorithms::FindSpherePlaneCollisionPoints(const SphereCollider *a, const Transform2D *ta, const PlaneCollider *b, const Transform2D *tb)
{
    // bool spherePlaneCollision(const Vector2f& sphere_center, float sphere_radius,
    //                 const Vector2f& plane_normal, const Vector2f& plane_point, float plane_length) {
    CollisionPoints ret;
    float distance_to_plane = (ta->pos - tb->pos).dot(b->normal);
    float depth = ta->scale.x - distance_to_plane;
    if (depth > 0 && abs(distance_to_plane) <= b->distance / 2)
    {
        ret.hasCollision = true;
        ret.normal = b->normal;
        ret.depth = depth;
    }
    else
    {
        ret.hasCollision = false;
    }
}
CollisionPoints collisionalgorithms::FindPlaneSphereCollisionPoints(const PlaneCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb)
{
}