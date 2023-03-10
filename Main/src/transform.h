#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Arduino.h>
#include <constants.h>
#include <utils.h>
#include <vec.h>

/**
 * @brief The Transform object is a data class that holds values pertaining to transform in a 2D space
 * This includes the position, rotation, and scale of an object
 * This object type is to be used in the 2D Domain, to represent the transform of a 3D object,
 */
class Transform2D
{
private:
    /* data */
public:
    Vec2 pos;
    Vec2 rot;
    Vec2 scale;

    Transform2D &setScale(Vec2 scale_)
    {
        scale = scale_;
        return *this;
    }
    Transform2D &setRotation(Vec2 rot_)
    {
        rot = rot_;
        return *this;
    }
    Transform2D &setPosition(Vec2 pos_)
    {
        pos = pos_;
        return *this;
    }

    Transform2D(Vec2 scale_ = {100, 100}, Vec2 pos_ = {WIDTH / 2, HEIGHT / 2}, Vec2 rot_ = {0, 0})
    {
        pos = pos_;
        rot = rot_;
        scale = scale_;
    }
};

class Transform3D
{
private:
    /* data */
public:
    Vec2 pos;
    Vec2 rot;
    Vec2 scale;

    void setScale(Vec2 scale_) { scale = scale_; }
    void setRotation(Vec2 rot_) { rot = rot_; }
    void setPosition(Vec2 pos_) { pos = pos_; }

    Transform3D(Vec2 scale_, Vec2 pos_, Vec2 rot_);
    ~Transform3D();
};

#endif // !TRANSFORM_H