#include <demos/collision/collisiondemo.h>
CollisionDemo::CollisionDemo(/* args */)
{
}

CollisionDemo::~CollisionDemo()
{
}
void CollisionDemo::init()
{
    p.format_info.kerneling = 300;
    p.format_info.font_size = 400;
    text = (new GameObject2D(sentanceg))->setPosition({100, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    text->mIsDynamic = false;
    world.addObject(text);

    GameObject2D *ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2 - 400, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    ball->velocity = {10, 0};
    ball->mIsGravity = true;
    world.addObject(ball);
    ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2 + 400, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    ball->velocity = {-10, 0};
    ball->mIsGravity = true;
    world.addObject(ball);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}

void CollisionDemo::draw()
{
    world.draw();
}
void CollisionDemo::update()
{
    world.step(dt);

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void CollisionDemo::restart()
{
}