#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>

class ShapesDemo : public Demo
{
private:
    /* data */
public:
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    Graphic *cubeg = new Shape(Graphic::Rectangle);

    GameObject2D *cube;

    ShapesDemo(/* args */);
    ~ShapesDemo();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};

ShapesDemo::ShapesDemo(/* args */)
{
}

ShapesDemo::~ShapesDemo()
{
}
void ShapesDemo::init()

{
    p.format_info.kerneling = 300;
    p.format_info.font_size = 400;
    cube = (new GameObject2D(cubeg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({1000, 1000})->setColor((Color)WHITE)->fitColliderToObject();
    cube->is_static = true;
    // cube->setRotation(cube->transform->rot + Vec3({PI / 4, PI / 4, 0}));
    world.addObject(cube);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}
void ShapesDemo::play()
{
}

void ShapesDemo::pause()
{
}
void ShapesDemo::draw()
{
    world.draw();
}
void ShapesDemo::update()
{
    world.step(dt);

    cube->setRotation(cube->transform->rot + Vec3({PI / 10000, PI / 10000, 0}));
}

void ShapesDemo::restart()
{
}