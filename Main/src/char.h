#ifndef CHAR_H
#define CHAR_H

#include <Arduino.h>
#include <transform.h>
#include <mesh.h>
#include <graphic.h>
#include <pointer.h>
class Char
{
private:
    /* data */
public:
    Mesh m;
    Transform2D transform;
    Char(Mesh m_) { m = m_; }
    Char(char c_) { m = Mesh(c_); }
    Char(char c_, Transform2D transform_)
    {
        m = Mesh(c_);
        transform = transform_;
    }
};

#endif // !CHAR_H
