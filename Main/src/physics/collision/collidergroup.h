#pragma once
#include <physics/collision/collider.h>

typedef std::function<void()> ColliderCallback;

class ColliderGroup
{
private:
    ColliderCallback callback;
    /* data */
public:
    std::vector<Collider *> colliders;
    void addCollider(Collider *collider) { colliders.push_back(collider); }
    void trigger()
    {
        if (callback)
            callback();
    }
    void setTrigger(ColliderCallback callback_) { callback = callback_; }
    ColliderGroup(/* args */){};
    ~ColliderGroup(){};
};
