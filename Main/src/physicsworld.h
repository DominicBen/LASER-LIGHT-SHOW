#include <Arduino.h>
#include <vector>
#include <gameobject.h>
#include "solver.h"

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

PhysicsWorld2D::PhysicsWorld2D()
{
}
void PhysicsWorld2D::draw()
{

    for (GameObject2D *obj : objects)
    {
        obj->draw();
    }
}

void PhysicsWorld2D::fill(std::vector<GameObject2D *> objects_)
{
    objects = objects_;
}
void PhysicsWorld2D::resolveCollisions()
{
    Serial.println("===================== Collisions =============");
    std::vector<Collision> collisions;
    // Find all collisions between all objects
    for (GameObject2D *a : objects)
    {
        for (GameObject2D *b : objects)
        {

            if (a == b)
            {
                break;
            }
            if (!a->collider || !b->collider)
            {
                Serial.println("Missing collider on object, skipping");
                continue;
            }

            CollisionPoints points = a->collider->testCollision(a->transform, b->collider, b->transform);

            if (points.hasCollision)
            {
                collisions.emplace_back(a, b, points);
                Serial.println("collision detected");
            }
        }
    }
    // Move objects if they are colliding
    for (Solver *solver : solvers)
    {
        Serial.println("looking for  collisions to solve.....");
        solver->solve(collisions);
    }
}
void PhysicsWorld2D::addObject(GameObject2D *obj)
{
    objects.push_back(obj);
}
void PhysicsWorld2D::addSolver(Solver *sov)
{
    solvers.push_back(sov);
}
void PhysicsWorld2D::removeObject(GameObject2D *obj)
{
    // if (!obj)
    // {
    //     return;
    // }

    // auto itr = std::find(objects.begin(), objects.end(), obj);

    // if (itr == objects.end())
    // {
    //     return;
    // }
    // objects.erase(itr);
}

void PhysicsWorld2D::step(float dt)
{
    resolveCollisions();
    resolveWorldBounderies(dt);
    for (GameObject2D *obj : objects)
    {
        // Serial.println("Updating object force");
        obj->force += gravity * obj->mass;
        // Serial.println("Updating one object vel");
        obj->velocity += obj->force / obj->mass * dt;
        // Serial.println("Updating one object pos");
        obj->transform->pos += obj->velocity * dt;
        // Serial.println("Updating one object force");
        obj->force = Vec2(0, 0);
    }
}

void PhysicsWorld2D::resolveWorldBounderies(float dt)
{
    for (GameObject2D *obj : objects)
    {

        if (obj->transform->pos.y >= HEIGHT - obj->transform->scale.y)
        { // top bounce
            obj->transform->pos.y = HEIGHT - obj->transform->scale.y;
            obj->velocity.y *= -1;
        }
        if (obj->transform->pos.y <= obj->transform->scale.y)
        { // bottom bounce
            obj->transform->pos.y = obj->transform->scale.y;
            obj->velocity.y *= -1;
        }
        if (obj->transform->pos.x >= WIDTH - obj->transform->scale.x)
        { // right side
            obj->transform->pos.y = WIDTH - obj->transform->scale.x;
            obj->velocity.x *= -1;
        }
        if (obj->transform->pos.x <= obj->transform->scale.x)
        { // left goal
            obj->transform->pos.x = obj->transform->scale.x;
            obj->velocity.x *= -1;
        }
    }
}

PhysicsWorld2D::~PhysicsWorld2D()
{
}
