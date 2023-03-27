#include "collision.h"
#include "gameobject.h"
#include <vector>

#pragma once

class Solver
{
private:
    /* data */
public:
    virtual void solve(std::vector<Collision> collisions) = 0;
    Solver(/* args */){};
    ~Solver(){};
};

class PositionSolver : public Solver
{
private:
    /* data */
public:
    void solve(std::vector<Collision> collisions) override;
    PositionSolver(/* args */){};
    ~PositionSolver(){};
};

void PositionSolver::solve(std::vector<Collision> collisions)
{
    for (Collision collision : collisions)
    {
        Serial.println("Found a collision to solve, lets get on that");
        Serial.print(collision.a->transform->pos.x);
        Serial.print(",");
        Serial.println(collision.a->transform->pos.y);
        Vec2 posChange = collision.points.normal * (collision.points.depth / 2);
        Serial.print(posChange.x);
        Serial.print(",");
        Serial.println(posChange.y);
        collision.a->transform->pos += posChange;
        collision.b->transform->pos += (posChange * -1);
    }
}