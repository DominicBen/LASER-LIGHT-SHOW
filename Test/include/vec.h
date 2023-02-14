#ifndef VEC_H
#define VEC_H

#include <Arduino.h>
#include <utils.h>

class Vec2
{
private:
    /* data */
public:
    float x;
    float y;
    Vec2();
    Vec2(float x_, float y_);
    float magnitude() { return sqrt(x * x + y * y); };
    void normalize()
    {
        float mag = magnitude();
        x = x / mag;
        y = y / mag;
    }
    ~Vec2();

    static float distance(Vec2 a, Vec2 b);
    Vec2 operator-(Vec2 a) { return Vec2(x - a.x, y - a.y); }
    Vec2 operator+(Vec2 a) { return Vec2(x + a.x, y + a.y); }
    Vec2 operator*(Vec2 a) { return Vec2(x * a.x, y * a.y); }
    Vec2 operator/(Vec2 a) { return Vec2(x / a.x, y / a.y); }
};

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(float x_, float y_)
{
    x = x_;
    y = y_;
}

Vec2::~Vec2()
{
}

#endif // !VEC_H