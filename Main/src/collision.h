#pragma once

#include <transform.h>
#include <gameobject.h>

class Collider;
class SphereCollider;
class PlaneCollider;
class GameObject2D;

struct CollisionPoints
{
    Vec2 a;
    Vec2 b;
    Vec2 normal;
    float depth;
    bool hasCollision;
};

struct Collision
{
    GameObject2D *a;
    GameObject2D *b;
    CollisionPoints points;

    Collision(GameObject2D *a_, GameObject2D *b_, const CollisionPoints &points_) : a(a_), b(b_), points(points_)
    {
    }
};
namespace collisionalgorithms
{
    CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb)
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
    CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider *a, const Transform2D *ta, const PlaneCollider *b, const Transform2D *tb)
    {
    }
    CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb)
    {
    }
}

class Collider
{
private:
    /* data */
public:
    Collider(/* args */){};
    ~Collider(){};

    virtual CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, Transform2D *colliderTransform) const = 0;
    virtual CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, Transform2D *colliderTransform) const = 0;
    virtual CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, Transform2D *colliderTransform) const = 0;
};

class SphereCollider : public Collider
{
private:
    /* data */
public:
    Vec2 *center;
    float *radius;
    CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, Transform2D *colliderTransform) const override
    {
        // Serial.println("testing collision");
        return collider->testCollision(colliderTransform, this, transform);
    }
    CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, Transform2D *colliderTransform) const override
    {
        // Serial.println("testing collision");
        return collisionalgorithms::FindSphereSphereCollisionPoints(this, transform, sphere, colliderTransform);
    }
    CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, Transform2D *colliderTransform) const override
    {
        // Serial.println("testing collision");
        return collisionalgorithms::FindSpherePlaneCollisionPoints(this, transform, plane, colliderTransform);
    }

    SphereCollider(Vec2 *center_, float *radius_)
    {
        center = center_;
        radius = radius_;
    }
    SphereCollider(){};
    ~SphereCollider(){};
};

class PlaneCollider : public Collider
{
private:
    /* data */
public:
    Vec2 plane;
    float distance;

    CollisionPoints testCollision(const Transform2D *transform, const Collider *collider, Transform2D *colliderTransform) const override
    {
        return collider->testCollision(colliderTransform, this, transform);
    }
    CollisionPoints testCollision(const Transform2D *transform, const SphereCollider *sphere, Transform2D *colliderTransform) const override
    {
        return collisionalgorithms::FindPlaneSphereCollisionPoints(this, transform, sphere, colliderTransform);
    }
    CollisionPoints testCollision(const Transform2D *transform, const PlaneCollider *plane, Transform2D *colliderTransform) const override
    {
        return {};
    }
    PlaneCollider(/* args */){};
    ~PlaneCollider(){};
};
