#include <shape.h>

Shape::Shape(){};
Shape::Shape(Type type_) { type = type_; }
Shape::Shape(Type type_, Transform2D t_)
{
    type = type_;
    transform = t_;
}

Shape::~Shape()
{
}
