#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Arduino.h>
#include <utils.h>
#include <vec.h>

// const uint16_t WIDTH = 4096;
// const uint16_t HEIGHT = 4096;

class Transform
{
private:
    /* data */
public:
    Vec2 pos;
    Vec2 rot;
    Vec2 scale;

    void set_scale(Vec2 scale_) { scale = scale_; }
    void set_rot(Vec2 rot_) { rot = rot_; }
    void set_pos(Vec2 pos_) { pos = pos_; }

    Transform(Vec2 scale_, Vec2 pos_, Vec2 rot_);
    ~Transform();
};

Transform::Transform(Vec2 scale_ = {100, 100}, Vec2 pos_ = {WIDTH / 2, HEIGHT / 2}, Vec2 rot_ = {0, 0})
{
    pos = pos_;
    rot = rot_;
    scale = scale_;
}

Transform::~Transform()
{
}

#endif // !TRANSFORM_H