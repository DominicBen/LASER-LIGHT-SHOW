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
    collider = new SphereCollider();
    transform = new Transform2D();
}

GameObject2D::~GameObject2D()
{
    free(collider);
    free(graphic);
    free(transform);
}
