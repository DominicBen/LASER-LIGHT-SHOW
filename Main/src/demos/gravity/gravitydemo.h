#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <graphics/sentence.h>
class GravityDemo : public Demo
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

    GravityDemo(/* args */);
    ~GravityDemo();

    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};
