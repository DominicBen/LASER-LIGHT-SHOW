#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <graphics/sentence.h>
class CollisionDemo : public Demo
{
private:
    /* data */
public:
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    Graphic *ballg = new Shape(Graphic::Circle);
    Graphic *sentanceg = new Sentence("collision");
    GameObject2D *text;

    CollisionDemo(/* args */);
    ~CollisionDemo();

    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};
