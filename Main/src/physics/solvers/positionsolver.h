#pragma once
#include <physics/solvers/solver.h>

class PositionSolver : public Solver
{
private:
    /* data */
public:
    void solve(std::vector<Collision> collisions) override;
    PositionSolver(/* args */){};
    ~PositionSolver(){};
};