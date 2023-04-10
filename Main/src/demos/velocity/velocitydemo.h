#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <graphics/sentence.h>
class VelocityDemo : public Demo
{
private:
    /* data */
public:
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    int32_t xspeed = random(10) - 5;
    int32_t yspeed = random(10) - 5;

    GameObject2D *ball;

    VelocityDemo(/* args */);
    ~VelocityDemo();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};
