#pragma once
#include <physics/collision/collider.h>
#include <gameobject.h>
class GameObject2D;

typedef std::function<void(GameObject2D *parent, GameObject2D *other)> ColliderCallback;

class ColliderGroup
{
private:
    ColliderCallback callback;
    GameObject2D *parent;
    /* data */
public:
    std::vector<Collider *> colliders;
    void addCollider(Collider *collider) { colliders.push_back(collider); }
    void trigger(GameObject2D *other)
    {
        if (callback)
            callback(parent, other);
    }
    void setTrigger(ColliderCallback callback_)
    {

        callback = callback_;
    }
    ColliderGroup(GameObject2D *parent_) { parent = parent_; };
    ~ColliderGroup()
    {
        for (auto i : colliders)
        {
            delete i;
        }
    };
};
