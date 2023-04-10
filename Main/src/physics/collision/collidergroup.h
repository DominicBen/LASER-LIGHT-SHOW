#pragma once
#include <physics/collision/collider.h>
#include <gameobject.h>
class GameObject2D;

typedef std::function<void(GameObject2D *parent)> ColliderCallback;

class ColliderGroup
{
private:
    ColliderCallback callback;
    GameObject2D *parent;
    /* data */
public:
    std::vector<Collider *> colliders;
    void addCollider(Collider *collider) { colliders.push_back(collider); }
    void trigger()
    {
        if (callback)
            callback(parent);
    }
    void setTrigger(ColliderCallback callback_)
    {

        callback = callback_;
    }
    ColliderGroup(GameObject2D *parent_) { parent = parent_; };
    ~ColliderGroup(){};
};
