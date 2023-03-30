#pragma once

#include <transform.h>
#include <gameobject.h>
#include <collisionalgorithms.h>
#include <collider.h>
#include <planecollider.h>
#include <spherecollider.h>

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
