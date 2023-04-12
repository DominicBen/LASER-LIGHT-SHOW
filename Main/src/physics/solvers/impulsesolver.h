#pragma once
#include <physics/solvers/solver.h>
class ImpulseSolver : public Solver
{
private:
    /* data */
public:
    void solve(std::vector<Collision> collisions) override;
    ImpulseSolver(/* args */);
    ~ImpulseSolver();
};