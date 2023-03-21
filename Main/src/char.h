#ifndef CHAR_H
#define CHAR_H

#include <Arduino.h>
#include <transform.h>
#include <mesh.h>
#include <graphic.h>
#include <pointer.h>
class Char : public Graphic
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

    void draw()
    {

        Vec2 newpos;
        for (u_int16_t i = 0; i < m.travel_order.size(); i++)
        {
            // Increases size of vertices
            newpos.y = map(m.verticies[m.travel_order[i]].y, -1, 1, 0, transform.scale.y) + transform.pos.y;
            newpos.x = map(m.verticies[m.travel_order[i]].x, -1, 1, 0, transform.scale.x) + transform.pos.x;
            p.pointTo({newpos.x, newpos.y});
            p.toggleLed(m.led_info[i]);
        }
        p.toggleLed(LOW);
    }
};

#endif // !CHAR_H
