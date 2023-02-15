#ifndef VEC_H
#define VEC_H

#include <Arduino.h>
#include <utils.h>
/**
 * @brief A vector class for storing a 2d vector of floats
 * used mainly to represent points in 2d space
 */
class Vec2
{
private:
    /* data */
public:
    float x;
    float y;

    Vec2(float x_ = 0, float y_ = 0) { x = x_, y = y_; };

    float magnitude() { return sqrt(x * x + y * y); };

    static float distance(Vec2 a, Vec2 b) { return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)); }
    Vec2 operator-(Vec2 a) { return Vec2(x - a.x, y - a.y); }
    Vec2 operator+(Vec2 a) { return Vec2(x + a.x, y + a.y); }
    Vec2 operator*(Vec2 a) { return Vec2(x * a.x, y * a.y); }
    Vec2 operator/(Vec2 a) { return Vec2(x / a.x, y / a.y); }

    void normalize()
    {
        float mag = magnitude();
        x = x / mag;
        y = y / mag;
    }
    void mapVec(int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
    {
        x = map(x, old_min, old_max, new_min, new_max);
        y = map(y, old_min, old_max, new_min, new_max);
    }
    static Vec2 mapVec(Vec2 old_num, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
    {
        Vec2 new_num;
        new_num.x = map(old_num.x, old_min, old_max, new_min, new_max);
        new_num.y = map(old_num.y, old_min, old_max, new_min, new_max);
        return new_num;
    }
};
/**
 * @brief A vector class for storing a 3d vector of floats
 * used mainly to represent points in 3d space
 */
class Vec3
{
private:
    /* data */
public:
    float x;
    float y;
    float z;

    Vec3(float x_ = 0, float y_ = 0, float z_ = 0)
    {
        x = x_;
        y = y_;
        z = z_;
    }

    float magnitude() { return sqrt(x * x + y * y + z * z); };
    void normalize()
    {
        float mag = magnitude();
        x = x / mag;
        y = y / mag;
        z = z / mag;
    }
    static float distance(Vec2 a, Vec2 b) { return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)); }

    Vec3 operator-(Vec3 a) { return Vec3(x - a.x, y - a.y, z - a.z); }
    Vec3 operator+(Vec3 a) { return Vec3(x + a.x, y + a.y, z + a.z); }
    Vec3 operator*(Vec3 a) { return Vec3(x * a.x, y * a.y, z * a.z); }
    Vec3 operator/(Vec3 a) { return Vec3(x / a.x, y / a.y, z / a.z); }
};

#endif // !VEC_H