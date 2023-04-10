#include <demos/velocity/velocitydemo.h>
VelocityDemo::VelocityDemo(/* args */)
{
}

VelocityDemo::~VelocityDemo()
{
}
void VelocityDemo::init()
{
    ball = (new GameObject2D(new Shape(Shape::Circle)))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    ball->velocity = {xspeed, yspeed};
    ball->mIsGravity = false;
    world.addObject(ball);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}

void VelocityDemo::draw()
{
    world.draw();
}
void VelocityDemo::update()
{
    world.step(dt);

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void VelocityDemo::restart()
{
}