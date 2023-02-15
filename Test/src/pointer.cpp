#include <pointer.h>

Pointer::Pointer()
{
    cur_pos = {0, 0};
    pinMode(LED_PIN, OUTPUT);

    // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
    // For MCP4725A0 the address is 0x60 or 0x61
    // For MCP4725A2 the address is 0x64 or 0x65
    xdim.begin(0x63);
    ydim.begin(0x62);
}

void Pointer::draw_shape(Shape s)
{
    switch (s.type)
    {
    case Shape::Circle:
        draw_circle(s);
        break;
    case Shape::Square:
        draw_rect(s);
        break;
    case Shape::Rectange:
        draw_rect(s);
        break;
    case Shape::Triangle:
        /* code */
        break;
    case Shape::Star:
        /* code */
        break;
    case Shape::Polygon:
        /* code */
        break;
    case Shape::Diamond:
        /* code */
    case Shape::AlphaNumeric:
        /* code */
        break;
    default:
        break;
    }
}

void Pointer::move_towards(Vec2 pos, uint16_t delay_time)
{
    int16_t xstep = (pos.x - cur_pos.x) >= 0 ? 1 : -1;
    int16_t ystep = (pos.y - cur_pos.y) >= 0 ? 1 : -1;
    Vec2 newPos = cur_pos;

    while (cur_pos.x != pos.x || cur_pos.y != pos.y)
    {
        if (cur_pos.x != pos.x)
        {
            newPos.x += xstep;
        }
        if (cur_pos.y != pos.y)
        {
            newPos.x += ystep;
        }

        point_to(newPos);
        delay(delay_time);
    }
}

void Pointer::point_to(Vec2 pos)
{
    if (pos.x != cur_pos.x)
    {
        xdim.setVoltage(clamp<uint16_t>(pos.x, 0, WIDTH), false, I2C_CLOCK);
        cur_pos.x = pos.x;
    }
    if (pos.y != cur_pos.y)
    {
        ydim.setVoltage(clamp<uint16_t>(pos.y, 0, HEIGHT), false, I2C_CLOCK);
        cur_pos.y = pos.y;
    }
}
void Pointer::toggle_led()
{
    digitalToggle(LED_PIN);
}
void Pointer::toggle_led(int8_t state)
{
    digitalWrite(LED_PIN, state);
}

void Pointer::draw_circle(Shape c)
{
    uint32_t counter;
    toggle_led();
    for (counter = 0; counter < c.res * 2; counter++)
    {
        // Serial.println(normalize(sin(counter/slowness),-1,1,0,4095));
        double val = ((2 * PI) / c.res) * counter;

        uint16_t xmin = c.t.pos.x - c.t.scale.x;
        uint16_t xmax = c.t.pos.x + c.t.scale.x;
        uint16_t ymin = c.t.pos.y - c.t.scale.y;
        uint16_t ymax = c.t.pos.y + c.t.scale.y;

        Vec2 new_pos = {map((float)sin(val), -1, 1, xmin, xmax), map((float)cos(val), -1, 1, ymin, ymax)};
        // Serial.println(new_pos.y);
        point_to(new_pos);
    }
    toggle_led();
}

void Pointer::draw_rect(Shape s)
{
    float leftbound = s.t.pos.x - s.t.scale.x;
    float rightbound = s.t.pos.x + s.t.scale.x;
    float bottombound = s.t.pos.y - s.t.scale.y;
    float topbound = s.t.pos.y + s.t.scale.y;
    // Move Pointer to bottom left position
    point_to({leftbound, bottombound});
    delayMicroseconds(s.res);
    // Draw the rectangle
    toggle_led(HIGH);
    point_to({leftbound, topbound});
    delayMicroseconds(s.res);
    point_to({rightbound, topbound});
    delayMicroseconds(s.res);
    point_to({rightbound, bottombound});
    delayMicroseconds(s.res);
    point_to({leftbound, bottombound});
    delayMicroseconds(s.res);
    // Turn off the laser
    toggle_led(LOW);
}

void Pointer::draw_grid(Grid g)
{
    for (int16_t i = -g.cols / 2; i <= g.cols / 2; i++)
    {
        for (int16_t j = -g.rows / 2; j <= g.rows / 2; j++)
        {
            float newx = (WIDTH / 2) + (g.s.t.scale.x * 2 * i);
            float newy = (HEIGHT / 2) + (g.s.t.scale.y * 2 * j);
            g.s.t.pos = {newx, newy};
            draw_shape(g.s);
        }
    }
}

// void Pointer::draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols)
// {
//     struct Point3D vertex[8] = {{-1, 1, -1}, {1, 1, -1}, {-1, -1, -1}, {1, -1, -1}, {-1, 1, 1}, {1, 1, 1}, {-1, -1, 1}, {1, -1, 1}};
// }

void Pointer::draw_mesh(Mesh m)
{
    Vec2 newpos;
    // delay(1000);
    for (u_int16_t i = 0; i < m.travel_order.size(); i++)
    {
        newpos = Vec2::mapVec(m.verticies[m.travel_order[i]], -1, 1, 0, 1000);
        newpos.x += WIDTH / 2;
        newpos.y += HEIGHT / 2;
        point_to({newpos.x, newpos.y});

        delayMicroseconds(400);

        if (!m.led_info[i])
        {
            delayMicroseconds(400);
        }
        toggle_led(m.led_info[i]);
    }
}

void Pointer::draw_symbol(Symbol s, bool first_letter)
{
    int16_t delay_mod = 400;
    Vec2 newpos;
    bool past_first = false;
    for (u_int16_t i = 0; i < s.m.travel_order.size(); i++)
    {
        newpos.x = map(s.m.verticies[s.m.travel_order[i]].x, -1, 1, 0, s.t.scale.x) + s.t.pos.x;
        newpos.y = map(s.m.verticies[s.m.travel_order[i]].y, -1, 1, 0, s.t.scale.y) + s.t.pos.y;
        point_to({newpos.x, newpos.y});

        if (first_letter && !past_first)
        {
            past_first = true;
            delayMicroseconds(delay_mod / 2);
        }
        delayMicroseconds(delay_mod);

        if (!s.m.led_info[i])
        {
            delayMicroseconds(0);
        }
        toggle_led(s.m.led_info[i]);
    }
    toggle_led(LOW);
}
void Pointer::draw_sentence(Sentence sen)
{
    point_to({sen.t.pos.x, sen.t.pos.y});
    int16_t sent_size = sen.word.size();
    int16_t line_count = 0;

    Serial.println("Drawing sentence of length");
    Serial.println(sent_size);

    Vec2 newPos = {sen.t.pos.x, sen.t.pos.y};

    Transform2D t({(float)sen.font_size, (float)sen.font_size}, newPos);
    Symbol sym = sen.word[0];
    sym.t = t;
    Serial.println("drawing a letter");
    draw_symbol(sym, true);
    for (int i = 1; i < sent_size; i++)
    {
        newPos = {newPos.x + sen.kerneling, newPos.y};
        if (newPos.x + sen.kerneling >= WIDTH)
        {
            line_count++;
            newPos = {sen.t.pos.x, newPos.y - sen.font_size * 2};
        }
        Transform2D t({(float)sen.font_size, (float)sen.font_size}, newPos);
        Symbol sym = sen.word[i];
        sym.t = t;
        Serial.println("drawing a letter");
        draw_symbol(sym, false);
        // delay(500);
    }
    toggle_led(LOW);
}