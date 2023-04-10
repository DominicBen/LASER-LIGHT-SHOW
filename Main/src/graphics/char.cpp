#include <graphics/char.h>

void Char::draw(Transform2D transform, Color c)
{
    Vec2 newpos;
    for (u_int16_t i = 0; i < m.travel_order.size(); i++)
    {
        // Increases size of vertices
        newpos.y = map(m.verticies[m.travel_order[i]].y, -1, 1, 0, transform.scale.y) + transform.pos.y;
        newpos.x = map(m.verticies[m.travel_order[i]].x, -1, 1, 0, transform.scale.x) + transform.pos.x;
        p.pointTo({newpos.x, newpos.y});
        p.setColor(c);
        p.setLed(!m.led_info[i]);
    }
    p.setLed(HIGH);
}