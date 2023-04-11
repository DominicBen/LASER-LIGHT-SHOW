#include <graphics/char.h>

void Char::draw(Transform2D transform, Color c)
{
    Vec2 newpos;
    if (type == SmallCircle)
    {
        transform.scale = transform.scale * 2;
    }
    for (u_int16_t i = 0; i < m.travel_order.size(); i++)
    {
        // Increases size of vertices
        newpos.y = map(m.verticies[m.travel_order[i]].y, -1, 1, -transform.scale.y / 2, transform.scale.y / 2) + transform.pos.y;
        newpos.x = map(m.verticies[m.travel_order[i]].x, -1, 1, -transform.scale.x / 2, transform.scale.x / 2) + transform.pos.x;
        p.pointTo({newpos.x, newpos.y});
        p.setColor(c);
        p.setLed(!m.led_info[i]);
    }
    p.setLed(HIGH);
}