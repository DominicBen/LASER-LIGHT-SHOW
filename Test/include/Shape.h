#ifndef SHAPE_H
#define SHAPE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Point.h>

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

    Point2D pos;
    Type type;
    int16_t x_scale = 100;
    int16_t y_scale = 100;
    int16_t x_vel = 100;
    int16_t y_vel = 100;
    u_int32_t res;
    Shape(Type type_, int16_t x_scale_, int16_t y_scale_, Point2D pos_, int16_t x_vel_, int16_t y_vel_);
    Shape(){};
    ~Shape();
};

Shape::Shape(Type type_, int16_t x_scale_ = 100, int16_t y_scale_ = 100, Point2D pos_ = {WIDTH / 2, HEIGHT / 2}, int16_t x_vel_ = 0, int16_t y_vel_ = 0)
{
    pos = pos_;
    x_scale = x_scale_;
    y_scale = y_scale_;
    x_vel = x_vel_;
    y_vel = y_vel_;
    type = type_;
    switch (type)
    {
    case Shape::Circle:
        res = 100;
        break;
    case Shape::Square:
        res = 100;
        break;
    case Shape::Rectange:
        res = 100;
        break;
    case Shape::Triangle:
        res = 100;
        break;
    case Shape::Star:
        res = 100;
        break;
    case Shape::Polygon:
        res = 100;
        break;
    case Shape::Diamond:
        res = 100;
    case Shape::AlphaNumeric:
        res = 100;
        break;
    default:
        break;
    }
}

Shape::~Shape()
{
}

class Grid : public Shape
{
private:
    /* data */
public:
    int16_t rows = 3;
    int16_t cols = 3;

    void operator=(Shape s);

    Grid();
    ~Grid();
};

void Grid::operator=(Shape s)
{
    pos = s.pos;
    type = s.type;
    x_scale = s.x_scale;
    y_scale = s.y_scale;
    x_vel = s.x_vel;
    y_vel = s.y_vel;
    res = s.res;
}

Grid::Grid()
{
}

Grid::~Grid()
{
}

#endif