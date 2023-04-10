#include <demos/ilda/cube3d/cube3dilda.h>

Cube3D::Cube3D(/* args */)
{
}

Cube3D::~Cube3D()
{
}
void Cube3D::init()
{
    cube = (new GameObject2D(cubeg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({4000, 4000})->setColor((Color)WHITE);
    cube->is_static = true;
}
void Cube3D::play()
{
}

void Cube3D::pause()
{
}
void Cube3D::draw()
{
    cube->draw();
}
void Cube3D::update()
{

    // cube->setRotation(cube->transform->rot + Vec3({PI / 1000, PI / 1000, 0}));
}

void Cube3D::restart()
{
}