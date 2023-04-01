#include <gameobject.h>
void GameObject2D::draw()
{
    graphic->draw(*transform, cur_color);
}

void GameObject2D::update()
{
}

GameObject2D::GameObject2D(Graphic *g)
{
    graphic = g;
    transform = new Transform2D();
}
GameObject2D::GameObject2D(Graphic *g, Collider *c)
{
    graphic = g;
    colliders.push_back(c);
    transform = new Transform2D();
}

GameObject2D::~GameObject2D()
{
    // free(collider);
    colliders.empty();
    free(graphic);
    free(transform);
}
GameObject2D *GameObject2D::fitColliderToObject()
{
    colliders.clear();
    Serial.println("fitCollider::adding collider");
    Serial.println(graphic->type);
    switch (graphic->type)
    {

    case Graphic::Circle:
        Serial.println("fitCollider::added collider to Circle");
        colliders.push_back(new SphereCollider());
        break;
    case Graphic::Rectangle:
        Serial.println("fitCollider::added collider to rectangle");
        Collider *topside = new PlaneCollider({0, transform->scale.y / 2}, {0, 1}, transform->scale.x);
        Collider *rightside = new PlaneCollider({transform->scale.x / 2, 0}, {1, 0}, transform->scale.y);
        Collider *bottomside = new PlaneCollider({0, -transform->scale.y / 2}, {0, -1}, transform->scale.x);
        Collider *leftside = new PlaneCollider({-transform->scale.x / 2, 0}, {-1, 0}, transform->scale.y);
        colliders.push_back(topside);
        colliders.push_back(rightside);
        colliders.push_back(bottomside);
        colliders.push_back(leftside);
        break;

    default:
        Serial.println("fitCollider::added collider to defualt");
        colliders.push_back(new SphereCollider());

        break;
    }

    return this;
}
