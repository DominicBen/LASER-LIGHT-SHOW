#pragma once
#include <Arduino.h>
#include <vector>
#include <gameobject.h>
#include "solvers/solver.h"

class Solver;
class Collision;
class PhysicsWorld2D
{
private:
    /* data */
    std::vector<GameObject2D *> objects;
    std::vector<Solver *> solvers;
    Vec2 gravity = {0, -9.81};

public:
    PhysicsWorld2D();
    void step(float dt);
    void addObject(GameObject2D *obj);
    void addSolver(Solver *sov);
    void removeObject(GameObject2D *obj);
    void step();
    void draw();
    void resolveCollisions();
    void resolveWorldBounderies(float dt);
    void fill(std::vector<GameObject2D *> objects_);
    ~PhysicsWorld2D();
};
