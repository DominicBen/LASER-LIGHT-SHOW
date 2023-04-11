#pragma once
#include <Arduino.h>
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
    template <typename T>

    Vec2(T x_, T y_)
    {
        x = (float)x_, y = (float)y_;
    };
    Vec2(float x_ = 0, float y_ = 0) { x = x_, y = y_; };

    // Operators
    Vec2 operator-(const Vec2 a) const { return Vec2(x - a.x, y - a.y); }
    Vec2 operator+(const Vec2 a) const { return Vec2(x + a.x, y + a.y); }
    Vec2 operator*(const Vec2 a) const { return Vec2(x * a.x, y * a.y); }
    Vec2 operator/(const Vec2 a) const { return Vec2(x / a.x, y / a.y); }
    Vec2 operator-(const float a) const { return Vec2(x - a, y - a); }
    Vec2 operator+(const float a) const { return Vec2(x + a, y + a); }
    Vec2 operator*(const float a) const { return Vec2(x * a, y * a); }
    Vec2 operator/(const float a) const { return Vec2(x / a, y / a); }

    Vec2 &operator-=(Vec2 a)
    {
        x = x - a.x;
        y = y - a.y;
        return *this;
    }
    Vec2 &operator+=(Vec2 a)
    {
        x = x + a.x;
        y = y + a.y;
        return *this;
    }
    Vec2 &operator*=(Vec2 a)
    {
        x = x * a.x;
        y = y * a.y;
        return *this;
    }
    Vec2 &operator/=(Vec2 a)
    {
        x = x / a.x;
        y = y / a.y;
        return *this;
    }
    Vec2 &operator-=(float a)
    {
        x = x - a;
        y = y - a;
        return *this;
    }
    Vec2 &operator+=(float a)
    {
        x = x + a;
        y = y + a;
        return *this;
    }
    Vec2 &operator*=(float a)
    {
        x = x * a;
        y = y * a;
        return *this;
    }
    Vec2 &operator/=(float a)
    {
        x = x / a;
        y = y / a;
        return *this;
    }
    float magnitude() { return sqrt(x * x + y * y); };
    static float distance(Vec2 a, Vec2 b) { return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)); }

    Vec2 &normalize()
    {
        float mag = magnitude();
        x = x / mag;
        y = y / mag;
        return *this;
    }
    Vec2 &mapVec(int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
    {
        x = map(x, old_min, old_max, new_min, new_max);
        y = map(y, old_min, old_max, new_min, new_max);
        return *this;
    }
    Vec2 &mapX(int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
    {
        x = map(x, old_min, old_max, new_min, new_max);
        // y = map(y, old_min, old_max, new_min, new_max);
        return *this;
    }
    Vec2 &mapY(int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
    {
        // x = map(x, old_min, old_max, new_min, new_max);
        y = map(y, old_min, old_max, new_min, new_max);
        return *this;
    }
    Vec2 &absVec()
    {
        x = abs(x);
        y = abs(y);
        return *this;
    }
    float dot(Vec2 a) const
    {
        return (x * a.x + y * a.y);
    }
    Vec2 &clamp(float min, float max)
    {
        if (x > max)
        {
            x = max;
            y = max;
        }
        else if (x < min)
        {
            x = min;
            y = max;
        }

        return *this;
    }
    static Vec2 mapVec(Vec2 old_num, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
    {
        Vec2 new_num;
        new_num.x = map(old_num.x, old_min, old_max, new_min, new_max);
        new_num.y = map(old_num.y, old_min, old_max, new_min, new_max);
        return new_num;
    }

    float cubicEaseOut(float t)
    {
        float f = t - 1.0;
        return f * f * f + 1.0;
    }
    Vec2 lerp(Vec2 a, Vec2 b, float duration, float currentTime)
    {
        float t = fmin((currentTime) / duration, 1.0); // calculate progress from start time and duration, and cap at 1.0
        float easedT = cubicEaseOut(t);                // apply ease-out formula to progress
        float x = a.x + (b.x - a.x) * easedT;          // interpolate x value
        float y = a.y + (b.y - a.y) * easedT;          // interpolate y value
        return Vec2(x, y);                             // return interpolated Vec2
    }
    void print() const
    {
        Serial.print("{");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print("}");
        Serial.println("");
    }
};

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
