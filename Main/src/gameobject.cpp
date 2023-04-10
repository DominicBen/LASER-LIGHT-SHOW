#include <gameobject.h>
void GameObject2D::draw()
{
    if (mIsDrawn)
        graphic->draw(*transform, cur_color);
}

void GameObject2D::update()
{
    graphic->update();
}

GameObject2D::GameObject2D(Graphic *g)
{
    graphic = g;
    transform = new Transform2D();
}
GameObject2D::GameObject2D(Graphic *g, Collider *c)
{
    graphic = g;
    mColliderGroup.colliders.push_back(c);
    transform = new Transform2D();
}
GameObject2D *GameObject2D::fitColliderToObject()
{
    mColliderGroup.colliders.clear();
    Serial.println("fitCollider::adding collider");
    Serial.println(graphic->type);

    switch (graphic->type)
    {

    case Graphic::Circle:
        Serial.println("fitCollider::added collider to Circle");
        mColliderGroup.colliders.push_back(new SphereCollider());
        break;
    case Graphic::Rectangle:
        Serial.println("fitCollider::added collider to rectangle");
        Collider *topside = new PlaneCollider({0, transform->scale.y / 2}, {0, 1}, transform->scale.x);
        Collider *rightside = new PlaneCollider({transform->scale.x / 2, 0}, {1, 0}, transform->scale.y);
        Collider *bottomside = new PlaneCollider({0, -transform->scale.y / 2}, {0, -1}, transform->scale.x);
        Collider *leftside = new PlaneCollider({-transform->scale.x / 2, 0}, {-1, 0}, transform->scale.y);
        mColliderGroup.colliders.push_back(topside);
        mColliderGroup.colliders.push_back(rightside);
        mColliderGroup.colliders.push_back(bottomside);
        mColliderGroup.colliders.push_back(leftside);
        break;

    default:
        Serial.println("fitCollider::added collider to defualt");
        mColliderGroup.colliders.push_back(new SphereCollider());

        break;
    }

    return this;
}
GameObject2D *GameObject2D::fitColliderToObject(ColliderCallback callback)
{
    mColliderGroup.setTrigger(callback);
    fitColliderToObject();
}
