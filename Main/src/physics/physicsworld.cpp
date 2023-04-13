#include <physics/physicsworld.h>
#include <algorithm>

PhysicsWorld2D::PhysicsWorld2D()
{
}
void PhysicsWorld2D::draw()
{

    for (GameObject2D *obj : objects)
    {
        Serial.println("world::drawing obj");
        obj->draw();
    }
}

void PhysicsWorld2D::fill(std::vector<GameObject2D *> objects_)
{
    objects = objects_;
}
void PhysicsWorld2D::resolveTriggers(std::vector<Collision> collisions)
{
    for (auto i : collisions)
    {
        i.a->mColliderGroup.trigger();
        i.b->mColliderGroup.trigger();
    }
}
void PhysicsWorld2D::resolveCollisions()
{
    // Serial.println("===================== Collisions =============");
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
            if (a->mColliderGroup.colliders.empty() || b->mColliderGroup.colliders.empty())
            {
                // Serial.println("Missing collider on object, skipping");
                continue;
            }
            bool should_break = false;
            // Serial.println("Entering for loops");
            for (Collider *c1 : a->mColliderGroup.colliders)
            {
                if (should_break)
                    break;
                for (Collider *c2 : b->mColliderGroup.colliders)
                {
                    if (should_break)
                        break;
                    CollisionPoints points = c1->testCollision(a->transform, c2, b->transform);

                    if (points.hasCollision)
                    {
                        collisions.emplace_back(a, b, points);
                        Serial.println("collision detected");
                        should_break = true;
                    }
                }
            }
        }
    }
    // Move objects if they are colliding
    for (Solver *solver : solvers)
    {
        // Serial.println("looking for  collisions to solve.....");
        solver->solve(collisions);
    }
    resolveTriggers(collisions);
}
void PhysicsWorld2D::addObject(GameObject2D *obj)
{
    objects.push_back(obj);
}
void PhysicsWorld2D::addSolver(Solver *sov)
{
    solvers.push_back(sov);
}
void PhysicsWorld2D::reset(){
    for(auto i : objects)
    {
        delete i;
    }
    objects.clear();
}
void PhysicsWorld2D::cleanUpWorld()
{
    while (true)
    {
        /* code */
        for (size_t i = 0; i < objects.size(); i++)
        {

            if(objects[i]->mMarkedForDeletion)
            {
                Serial.println("World::clean:: removing obj");
                removeObject(objects[i]);
                Serial.println("World::clean:: obj removed");
                break;
            }
            if (i == objects.size()-1)
            {
                Serial.println("World::clean:: cleanup done");
                return;
            }
            
        }
    }
    
}

void PhysicsWorld2D::removeObject(GameObject2D *obj)
{
    Serial.println("World:: Deleting obj first");
    if (obj == NULL)
    {
        Serial.println("World:: obj is null");
        return;
    }
            Serial.println("World:: Deleting obj 2");

    auto it = std::find(objects.begin(), objects.end(), obj);
        Serial.println("World:: Deleting obj 3");

    if(it != objects.end()){
            Serial.println("World:: Deleting obj 4");

        objects.erase(it);
            Serial.println("World:: Deleting obj5");

        delete obj;
            Serial.println("World:: Deleting obj6");

        obj = NULL;
            Serial.println("World:: Deleting obj");

    }

}

void PhysicsWorld2D::step(float dt)
{

    for (GameObject2D *obj : objects)
    {
        if (!obj->mIsDynamic)
            continue;

        if (obj->mIsGravity)
            obj->force += gravity * obj->mass;
        obj->velocity += obj->force / obj->mass * dt;
        obj->transform->pos += obj->velocity * dt;
        obj->force = Vec2(0, 0);
    }
    resolveCollisions();
    if (mHasBorder)
        resolveWorldBounderies(dt);
}

void PhysicsWorld2D::resolveWorldBounderies(float dt)
{
    for (GameObject2D *obj : objects)
    {
        if (!obj->mIsDynamic)
            continue;

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
            obj->transform->pos.x = WIDTH - obj->transform->scale.x;
            obj->velocity.x *= -1;
        }
        if (obj->transform->pos.x <= obj->transform->scale.x)
        { // left goal
            obj->transform->pos.x = obj->transform->scale.x;
            obj->velocity.x *= -1;
        }
    }
}
