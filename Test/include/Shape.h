#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Point.h>



class Shape
{
private:
    /* data */
public:

    enum Type {
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
    Shape(Point2D pos_, int16_t x_scale_, int16_t y_scale_, int16_t x_vel_, int16_t y_vel_, Type type_);
    Shape(){};
    ~Shape();
};

Shape::Shape(Point2D pos_, int16_t x_scale_, int16_t y_scale_, int16_t x_vel_, int16_t y_vel_,  Type type_)
{
    pos = pos_;
    x_scale= x_scale_;
    y_scale= y_scale_;
    x_vel= x_vel_;
    y_vel= y_vel_;
    type = type_;
}

Shape::~Shape()
{

}


class Grid: public Shape
{
private:
    /* data */
public:
    int16_t rows = 3;
    int16_t cols = 3;
    
    Grid(/* args */);
    ~Grid();
};

Grid::Grid(/* args */)
{
}

Grid::~Grid()
{
    
}