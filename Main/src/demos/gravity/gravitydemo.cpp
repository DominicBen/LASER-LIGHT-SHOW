#include <demos/gravity/gravitydemo.h>
GravityDemo::GravityDemo(/* args */)
{
}

GravityDemo::~GravityDemo()
{
}
void GravityDemo::init()
{
    ball = (new GameObject2D(new Shape(Shape::Circle)))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    ball->velocity = {xspeed, yspeed};
    ball->mIsGravity = true;
    dt = 0.5;
    world.addObject(ball);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}

void GravityDemo::draw()
{
    world.draw();
}
void GravityDemo::update()
{
    world.step(dt);

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void GravityDemo::restart()
{
}