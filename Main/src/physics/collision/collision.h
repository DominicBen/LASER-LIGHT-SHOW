#pragma once

#include <dataobjects/transform.h>
#include <gameobject.h>
#include <physics/collision/collider.h>
#include <physics/collision/planecollider.h>
#include <physics/collision/spherecollider.h>
#include <physics/collision/collisionalgorithms.h>

class GameObject2D;

struct Collision
{
    GameObject2D *a;
    GameObject2D *b;
    CollisionPoints points;

    Collision(GameObject2D *a_, GameObject2D *b_, const CollisionPoints &points_) : a(a_), b(b_), points(points_)
    {
    }
};
