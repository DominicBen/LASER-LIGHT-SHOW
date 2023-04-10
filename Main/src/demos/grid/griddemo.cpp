#include <demos/grid/griddemo.h>

GridDemo::GridDemo(/* args */)
{
}

GridDemo::~GridDemo()
{
}
void GridDemo::init()
{
    p.format_info.kerneling = 300;
    p.format_info.font_size = 400;
    // text = (new GameObject2D(sentanceg))->setPosition({100, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    // text->is_static = true;
    // world.addObject(text);
    float spacing = 100;
    for (int i = -2; i < 3; i++)
    {
        for (int j = -2; j < 3; j++)
        {
            GameObject2D *ball = (new GameObject2D(squareg))
                                     ->setPosition({WIDTH / 2 + spacing * i, HEIGHT / 2 + spacing * j})
                                     ->setScale({spacing, spacing})
                                     ->setColor((Color)WHITE);
            ball->is_gravity = false;
            ball->is_static = true;
            world.addObject(ball);
        }
    }
    world.addSolver(&solver1);
    world.addSolver(&solver2);
}
void GridDemo::play()
{
}

void GridDemo::pause()
{
}
void GridDemo::draw()
{
    world.draw();
}
void GridDemo::update()
{
    world.step(dt);

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void GridDemo::restart()
{
}