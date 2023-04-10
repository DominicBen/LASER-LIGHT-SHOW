#include <demos/balls/ballsdemo.h>
BallDemo::BallDemo(/* args */)
{
}

BallDemo::~BallDemo()
{
}
void BallDemo::init()
{
    p.format_info.kerneling = 300;
    p.format_info.font_size = 400;
    text = (new GameObject2D(sentanceg))->setPosition({100, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    text->is_static = true;
    world.addObject(text);
    for (size_t i = 0; i < 6; i++)
    {
        uint32_t offset = random(400) - 200;
        uint32_t coolrandomcolor = random(6);
        int32_t xspeed = random(10) - 5;
        int32_t yspeed = random(10) - 5;
        GameObject2D *ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2 + offset, HEIGHT / 2 + offset})->setScale({100 * (coolrandomcolor + 1) / 2, 100 * (coolrandomcolor + 1) / 2})->setColor((Color)WHITE)->fitColliderToObject();
        ball->velocity = {xspeed, yspeed};
        ball->mass = ball->transform->scale.x * ball->transform->scale.y * PI;
        world.addObject(ball);
    }

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}
void BallDemo::play()
{
}

void BallDemo::pause()
{
}
void BallDemo::draw()
{
    world.draw();
}
void BallDemo::update()
{
    world.step(dt);

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void BallDemo::restart()
{
}