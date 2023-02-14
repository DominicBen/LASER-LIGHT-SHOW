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
    Transform t;
    Mesh m;

    u_int32_t res = 400;
    Symbol(/* args */);
    Symbol(Mesh m);
    ~Symbol();
};

Symbol::Symbol(Mesh m_)
{
    m = m_;
}

Symbol::~Symbol()
{
}

#endif // !SYMBOL_H#define SYMBOL_H
