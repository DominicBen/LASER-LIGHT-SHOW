#include <demos/ilda/selection/selectilda.h>

ILDADemo::ILDADemo(/* args */)
{
}

ILDADemo::~ILDADemo()
{
}
void ILDADemo::init()
{
    a = 0;
    cube = (new GameObject2D(new ILDA(files[(int)a])))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({4000, 4000})->setColor((Color)WHITE);
    cube->mIsDynamic = false;
}

void ILDADemo::draw()
{

    cube->draw();
}
void ILDADemo::update()
{
    if (!mIsPaused)
        cube->update();
    // cube->setRotation(cube->transform->rot + Vec3({PI / 1000, PI / 1000, 0}));
}

void ILDADemo::restart()
{
    delete cube;
    init();
}