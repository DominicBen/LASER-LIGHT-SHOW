#include <physics/solvers/positionsolver.h>

void PositionSolver::solve(std::vector<Collision> collisions)
{
    for (Collision collision : collisions)
    {
        if (collision.a->mIsTrigger || collision.b->mIsTrigger)
            continue;

        Serial.println("PositionSolver::Found a collision to solve, lets get on that");
        Serial.print("PositionSolver::Position of collision");
        Serial.print(collision.a->transform->pos.x);
        Serial.print(",");
        Serial.println(collision.a->transform->pos.y);
        Vec2 posChange = collision.points.normal * (collision.points.depth);
        Serial.print("PositionSolver::Change of position for collision");
        Serial.print(posChange.x);
        Serial.print(",");
        Serial.println(posChange.y);

        if (collision.a->mIsDynamic)
        {
            Serial.println("PositionSolver::Updated object a");
            collision.a->transform->pos += posChange;
        }
        if (collision.b->mIsDynamic)
        {
            Serial.println("PositionSolver::Updated object b");
            Vec2 temp = (posChange * -1);
            temp.print();
            collision.b->transform->pos += temp;
        }
    }
}