struct CollisionPoints;

#include <transform.h>
#include <spherecollider.h>
#include <planecollider.h>

namespace collisionalgorithms
{
    CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb);

    CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider *a, const Transform2D *ta, const PlaneCollider *b, const Transform2D *tb);

    CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider *a, const Transform2D *ta, const SphereCollider *b, const Transform2D *tb);
};