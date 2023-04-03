#pragma once
#include <demos/demo.h>
#include <physicsworld.h>
#include <shape.h>

class RotatingCube : public Demo
{
private:
    /* data */
public:
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    Graphic *cubeg = new Shape(Graphic::Rectangle);

    GameObject2D *cube;

    RotatingCube(/* args */);
    ~RotatingCube();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};

RotatingCube::RotatingCube(/* args */)
{
}

RotatingCube::~RotatingCube()
{
}
void RotatingCube::init()

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
void RotatingCube::play()
{
}

void RotatingCube::pause()
{
}
void RotatingCube::draw()
{
    world.draw();
}
void RotatingCube::update()
{
    world.step(dt);

    cube->setRotation(cube->transform->rot + Vec3({PI / 10000, PI / 10000, 0}));
}

void RotatingCube::restart()
{
}