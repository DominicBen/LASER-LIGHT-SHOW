#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <dataobjects/transform.h>
#include <graphics/graphic.h>
#include <physics/collision/collision.h>
#include <physics/collision/collider.h>
#include <physics/collision/collidergroup.h>
#include <vector>

class GameObject2D
{
private:
    // Collision Box
    // Graphic

public:
    Graphic *graphic;
    Transform2D *transform;
    // std::vector<Collider *> colliders;
    ColliderGroup mColliderGroup = ColliderGroup(this);
    String mID;
    bool mMarkedForDeletion = false;

    Color cur_color = RED;
    // Physics Info
    Vec2 velocity = {0, 0};
    Vec2 force = {0, 0};
    float mass = 1;
    // Physic Bools
    bool mIsDynamic = true;  // weather an object is completly immobile and uneffected by physics
    bool mIsGravity = true;  // whether an object is effected by gravity
    bool mIsDrawn = true;    // Weahter an object is drawn on a drawn call, Good for triggers
    bool mIsTrigger = false; // Whether an object is effected by collision solvers
    // functions
    void update();
    void draw();
    GameObject2D *setColor(Color c)
    {
        cur_color = c;
        return this;
    }

    GameObject2D *setScale(Vec2 scale_)
    {
        transform->setScale(scale_);
        return this;
    }
    GameObject2D *setRotation(Vec3 rot_)
    {
        transform->setRotation(rot_);
        return this;
    }
    GameObject2D *setPosition(Vec2 pos_)
    {
        transform->setPosition(pos_);
        return this;
    }
    GameObject2D *fitColliderToObject(ColliderCallback callback);
    GameObject2D *fitColliderToObject();

    GameObject2D *changeGraphic(Graphic *g)
    {
        delete graphic;
        graphic = g;
        return this;
    }
    GameObject2D(/* args */);
    GameObject2D(Graphic *g);
    GameObject2D(Graphic *g, String id);

    ~GameObject2D()
    {

        delete transform;
    }
};

#endif // !GAMEOBJECT_H