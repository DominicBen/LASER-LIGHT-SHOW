#pragma once
#include <demos/demo.h>
#include <physicsworld.h>
#include <shape.h>
#include <ilda/ILDA.h>
static const char *files[] = {
    "ilda/cube.ild",    // works
    "ilda/money.ild",   // kinda work
    "ilda/wall.ild",    // doesnt work
    "ilda/tunnel.ild",  // doesnt work
    "ilda/nasa.ild",    // doesnt work
    "ilda/magic.ild",   // doesnt wark
    "ilda/wheel.ild",   // doesnt work
    "ilda/tunnel2.ild", // doesnt work
    "ilda/land.ild",    // doesnt work
};
class Cube3D : public Demo
{
private:
    /* data */
public:
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    Graphic *cubeg = new ILDA(files[0]);

    GameObject2D *cube;

    Cube3D(/* args */);
    ~Cube3D();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};

Cube3D::Cube3D(/* args */)
{
}

Cube3D::~Cube3D()
{
}
void Cube3D::init()
{
    p.format_info.kerneling = 300;
    p.format_info.font_size = 400;
    cube = (new GameObject2D(cubeg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({1000, 1000})->setColor((Color)WHITE);
    cube->is_static = true;
    world.addObject(cube);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}
void Cube3D::play()
{
}

void Cube3D::pause()
{
}
void Cube3D::draw()
{
    world.draw();
}
void Cube3D::update()
{
    world.step(dt);

    // cube->setRotation(cube->transform->rot + Vec3({PI / 1000, PI / 1000, 0}));
}

void Cube3D::restart()
{
}