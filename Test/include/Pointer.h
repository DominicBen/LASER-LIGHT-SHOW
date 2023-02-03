#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Shape.h>
#include <Utils.h>

const uint16_t LED_PIN = 5;

const uint16_t DEPTH = 100;
const uint32_t I2C_CLOCK = 1000000;

class Pointer
{
private:
    Adafruit_MCP4725 xdim;
    Adafruit_MCP4725 ydim;

    void draw_circle(Shape c);
    void draw_rect(Shape s);
    void draw_grid(Grid g);
    void draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols);

    void point_to(Point2D pos);
    void toggle_led();
    void toggle_led(int8_t state);

public:
    Point2D cur_pos;
    Pointer(/* args */);
    void draw_shape(Shape s);
};

Pointer::Pointer(/* args */)
{
    cur_pos = {0, 0};
}

void Pointer::point_to(Point2D pos)
{
    if (pos.x != cur_pos.x)
    {
        xdim.setVoltage(clamp<uint16_t>(pos.x, 0, HEIGHT), false, I2C_CLOCK);
    }
    else if (pos.y != cur_pos.y)
    {
        ydim.setVoltage(clamp<uint16_t>(pos.y, 0, WIDTH), false, I2C_CLOCK);
    }
    cur_pos = pos;
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
    for (counter = 0; counter < c.res * 2; counter++)
    {
        // Serial.println(normalize(sin(counter/slowness),-1,1,0,4095));
        double val = ((2 * PI) / c.res) * counter;

        uint16_t xmin = c.pos.x - c.x_scale;
        uint16_t xmax = c.pos.x + c.y_scale;
        uint16_t ymin = c.pos.y - c.x_scale;
        uint16_t ymax = c.pos.y + c.y_scale;

        Point2D new_pos = {normalize(sin(val), -1, 1, xmin, xmax), normalize(cos(val), -1, 1, ymin, ymax)};
        point_to(new_pos);
    }
}

void Pointer::draw_rect(Shape s)
{
    uint16_t leftbound = s.pos.x - s.x_scale;
    uint16_t rightbound = s.pos.x + s.x_scale;
    uint16_t bottombound = s.pos.y - s.y_scale;
    uint16_t topbound = s.pos.y + s.y_scale;

    point_to({leftbound, bottombound});
    delayMicroseconds(s.res);

    toggle_led(HIGH);
    point_to({leftbound, topbound});
    delayMicroseconds(s.res);
    point_to({rightbound, topbound});
    delayMicroseconds(s.res);
    point_to({rightbound, bottombound});
    delayMicroseconds(s.res);
    point_to({leftbound, bottombound});
    delayMicroseconds(s.res);
    toggle_led(LOW);
}

void Pointer::draw_grid(Grid g)
{
    for (int32_t i = -g.cols / 2; i <= g.cols / 2; i++)
    {
        for (int32_t j = -g.rows / 2; j <= g.rows / 2; j++)
        {
            draw_rect(g);
        }
    }
}

void Pointer::draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols)
{
    struct Point3D vertex[8] = {{-1, 1, -1}, {1, 1, -1}, {-1, -1, -1}, {1, -1, -1}, {-1, 1, 1}, {1, 1, 1}, {-1, -1, 1}, {1, -1, 1}};
}
