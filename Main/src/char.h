#ifndef CHAR_H
#define CHAR_H

#include <Arduino.h>
#include <transform.h>
#include <mesh.h>

class Char
{
private:
    /* data */
public:
    Transform2D transform;
    Mesh m;
    Char(Mesh m_) { m = m_; }
    Char(char c_) { m = Mesh(c_); }
    Char(char c_, Transform2D transform_)
    {
        m = Mesh(c_);
        transform = transform_;
    }
};

#endif // !CHAR_H
