#include <shape.h>

Shape::Shape(){};
Shape::Shape(Type type_) { type = type_; }
Shape::Shape(Type type_, Transform2D t_)
{
    type = type_;
    t = t_;
    res = 400;
}
Shape::Shape(Type type_, u_int32_t res_, Transform2D t_)
{
    type = type_;
    t = t_;
    res = res_;
}

Shape::~Shape()
{
}
