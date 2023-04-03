#ifndef CHAR_H
#define CHAR_H

#include <Arduino.h>
#include <transform.h>
#include <mesh.h>
#include <graphic.h>
#include <color.h>
#include <pointer.h>

class Char : public Graphic
{
private:
    /* data */
public:
    Mesh m;
    // Transform2D transform;
    Char(Mesh m_)
    {
        m = m_;
    }
    Char(char c_) { m = Mesh(c_); }
    // Char(char c_, Transform2D transform_)
    // {
    //     m = Mesh(c_);
    //     // transform = transform_;
    // }

    void draw(Transform2D transform, Color c) override;
};

#endif // !CHAR_H
