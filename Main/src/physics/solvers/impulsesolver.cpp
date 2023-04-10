#include <physics/solvers/impulsesolver.h>

ImpulseSolver::ImpulseSolver(/* args */)
{
}

ImpulseSolver::~ImpulseSolver()
{
}
void ImpulseSolver::solve(std::vector<Collision> collisions)
{
    for (Collision collision : collisions)
    {
        Serial.println("ImpulseSolver:: updating impulse");
        // Compute the relative velocity between the two spheres
        Vec2 relative_velocity = collision.b->velocity - collision.a->velocity;

        // Compute the velocity along the normal direction
        float velocity_along_normal = relative_velocity.dot(collision.points.normal * -1);

        // If the spheres are already moving apart, do nothing
        if (velocity_along_normal > 0)
        {
            Serial.println("ImpulseSolver:: vel along normal is positive");
            return;
        }

        // Compute the impulse scalar
        float e = 1.0; // coefficient of restitution
        float j = -(1.0 + e) * velocity_along_normal;
        if (!collision.a->is_static && !collision.b->is_static)
            j /= 1.0f / collision.b->mass + 1.0f / collision.a->mass;
        else if (!collision.a->is_static)
            j /= 1.0f / collision.a->mass;
        else if (!collision.b->is_static)
            j /= 1.0f / collision.b->mass;
        else
        {
            Serial.println("ImpulseSolver::Two Static objects colliding???");
            j = 0;
        }

        // Apply the impulse to the velocities
        Vec2 impulse = collision.points.normal * j * -1;
        Serial.println("ImpulseSolver:: object b speed");
        collision.b->velocity.print();
        Serial.println("ImpulseSolver:: impulse");
        impulse.print();

        if (!collision.a->is_static)
        {

            collision.a->velocity -= impulse * (1.0f / collision.a->mass);
            Serial.println("ImpulseSolver:: updating object a");
        }
        if (!collision.b->is_static)
        {
            collision.b->velocity += impulse * (1.0f / collision.b->mass);
            Serial.println("ImpulseSolver:: updating object b");
        }
    }
}
