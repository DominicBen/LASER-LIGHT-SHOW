#ifndef SYMBOL_H
#define SYMBOL_H

#include <Arduino.h>
#include <transform.h>
#include <mesh.h>

class Symbol
{
private:
    /* data */
public:
    Transform2D t;
    Mesh m;

    u_int32_t res = 400;
    Symbol(Mesh m_) { m = m_; }
};

#endif // !SYMBOL_H#define SYMBOL_H
