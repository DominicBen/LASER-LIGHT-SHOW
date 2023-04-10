#pragma once
#include <physics/collision/collision.h>
#include <gameobject.h>
#include <vector>

class Solver
{
private:
    /* data */
public:
    virtual void solve(std::vector<Collision> collisions) = 0;
    Solver(/* args */){};
    ~Solver(){};
};

#include <physics/solvers/impulsesolver.h>
#include <physics/solvers/positionsolver.h>