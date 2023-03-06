#ifndef SHAPE_H
#define SHAPE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <transform.h>

const u_int16_t CIRCLE_RESOLUTION = 15;

class Shape
{
private:
    /* data */
public:
    /// @brief A Enum representing the different possible types for each shape
    /// @example Circle Vs Square
    enum Type
    {
        Circle,
        Square,
        Rectangle,
        Triangle,
        Star,
        Polygon,
        Diamond,
        Grid,
        AlphaNumeric
    };
    /// @brief current type of this instance
    Type type;

    Transform2D transform;
    /// @brief Resolution of the shape, The higher this value is, the clearer the shape comes out, but the longer it takes to draw

    Shape();
    Shape(Type type_);
    Shape(Type type_, Transform2D t_);
    Shape(Type type_, u_int32_t res_, Transform2D t_);
    ~Shape();
};

class Grid
{
public:
    /// @brief The rows of shape s to be drawn
    int16_t rows = 3;
    /// @brief the cols of shape s to be drawn
    int16_t cols = 3;
    /// @brief The shape that is to be displayed in a grid fashion.
    Shape s;
    Grid(Shape s_) { s = s_; }
    Grid() {}
};

#endif