#ifndef POINTER_H
#define POINTER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Shape.h>
#include <Utils.h>

const uint16_t LED_PIN = 5;
const uint32_t I2C_CLOCK = 1000000;

class Pointer
{
private:
    // References to the x and y galvo outputs
    // Accepts voltage values from (0-4095)

    
    Adafruit_MCP4725 xdim;
    Adafruit_MCP4725 ydim;

    // Points the laser to a specific point on the screen, The bottom left is 0,0
    // WIDTH/2 , HEIGHT/2 is the middle of the screen
    void point_to(Point2D pos);
    // Toggles the state of the LED
    void toggle_led();
    // Sets the state of the led to state
    // Ex. HIGH -> on
    // LOW -> Off
    void toggle_led(int8_t state);

protected:
    Pointer();

public:
    // Singleton Constructors
    Pointer(const Pointer &) = delete;
    Pointer(Pointer &&) = delete;
    Pointer &operator=(const Pointer &) = delete;
    Pointer &operator=(Pointer &&) = delete;

    // Current position of the galvo, updated on point_to()
    Point2D cur_pos;

    // Draws any given shape s depending on its type
    void draw_shape(Shape s);

    void draw_circle(Shape c);
    void draw_rect(Shape s);

    // Draws a grid of shapes, shape is dependant on what is stored in Grid g
    void draw_grid(Grid g);

    void draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols);

    static Pointer &getInstance()
    {
        static Pointer instance; // Guaranteed to be destroyed.
                                 // Instantiated on first use.
        return instance;
    }
};

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

void Pointer::point_to(Point2D pos)
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

        uint16_t xmin = c.pos.x - c.x_scale;
        uint16_t xmax = c.pos.x + c.x_scale;
        uint16_t ymin = c.pos.y - c.y_scale;
        uint16_t ymax = c.pos.y + c.y_scale;

        Point2D new_pos = {(uint16_t)normalize(sin(val), -1, 1, xmin, xmax), (uint16_t)normalize(cos(val), -1, 1, ymin, ymax)};
        // Serial.println(new_pos.y);
        point_to(new_pos);
    }
    toggle_led();
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
    for (int16_t i = -g.cols / 2; i <= g.cols / 2; i++)
    {
        for (int16_t j = -g.rows / 2; j <= g.rows / 2; j++)
        {
            u_int16_t newx = (WIDTH / 2) + (g.s.x_scale * 2 * i);
            u_int16_t newy = (HEIGHT / 2) + (g.s.y_scale * 2 * j);
            g.s.pos = {newx, newy};
            draw_shape(g.s);
        }
    }
}

void Pointer::draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols)
{
    struct Point3D vertex[8] = {{-1, 1, -1}, {1, 1, -1}, {-1, -1, -1}, {1, -1, -1}, {-1, 1, 1}, {1, 1, 1}, {-1, -1, 1}, {1, -1, 1}};
}

#endif