#ifndef SHAPE_H
#define SHAPE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <point.h>
#include <transform.h>

class Shape
{
private:
    /* data */
public:
    enum Type
    {
        Circle,
        Square,
        Rectange,
        Triangle,
        Star,
        Polygon,
        Diamond,
        Grid,
        AlphaNumeric
    };
    Type type;

    // Point2D pos;
    // int16_t x_scale = 100;
    // int16_t y_scale = 100;
    // int16_t x_vel = 100;
    // int16_t y_vel = 100;

    Transform t;
    u_int32_t res = 400;
    // Shape(Type type_, u_int32_t res_, int16_t x_scale_, int16_t y_scale_, Point2D pos_, int16_t x_vel_, int16_t y_vel_);
    Shape();
    Shape(Type type_);
    Shape(Type type_, Transform t_);
    Shape(Type type_, u_int32_t res_, Transform t_);
    ~Shape();
};
Shape::Shape(){};
Shape::Shape(Type type_) { type = type_; }
Shape::Shape(Type type_, Transform t_)
{
    type = type_;
    t = t_;
    res = 400;
}
Shape::Shape(Type type_, u_int32_t res_, Transform t_)
{
    type = type_;
    t = t_;
    res = res_;
}

// Shape::Shape(Type type_, u_int32_t res_ = 100, int16_t x_scale_ = 100, int16_t y_scale_ = 100, Point2D pos_ = {WIDTH / 2, HEIGHT / 2}, int16_t x_vel_ = 0, int16_t y_vel_ = 0)
// {
//     pos = pos_;
//     x_scale = x_scale_;
//     y_scale = y_scale_;
//     x_vel = x_vel_;
//     y_vel = y_vel_;
//     type = type_;

//     switch (type)
//     {
//     case Shape::Circle:
//         res = 100;
//         break;
//     case Shape::Square:
//         res = 400;
//         break;
//     case Shape::Rectange:
//         res = 400;
//         break;
//     case Shape::Triangle:
//         res = 100;
//         break;
//     case Shape::Star:
//         res = 100;
//         break;
//     case Shape::Polygon:
//         res = 100;
//         break;
//     case Shape::Diamond:
//         res = 100;
//     case Shape::AlphaNumeric:
//         res = 100;
//         break;
//     default:
//         break;
//     }
//     res = res_;
// }

Shape::~Shape()
{
}

class Grid
{
private:
    /* data */
public:
    int16_t rows = 3;
    int16_t cols = 3;
    Shape s;
    Grid();
    Grid(Shape s);

    ~Grid();
};

Grid::Grid() {}

Grid::Grid(Shape s_)
{
    s = s_;
}

Grid::~Grid()
{
}

#endif