#include <vec.h>
#include <constants.h>
#include <transform.h>

class Physics2D
{
private:
    /* data */
public:
    Vec2 acceleration = {0, GRAVITY};
    Vec2 velocity = {0, 0};
    Transform2D *transform_of_root;

    Physics2D(Transform2D *transform_) { transform_of_root = transform_; }
    ~Physics2D(){};
    void update();
};

void Physics2D::update()
{
    transform_of_root->pos = transform_of_root->pos + velocity;
    velocity = velocity + acceleration;
}