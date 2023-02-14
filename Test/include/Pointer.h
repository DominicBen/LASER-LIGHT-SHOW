/**
 * @file Pointer.h
 * @author Laser Light Show
 * @brief Pointer is a singleton class incharge of moving where the laser projects on a screen
 * It has sole access to the movement of the xdim / ydim galvos, aswell as toggling the state of the led
 * Along with this control, Pointer has several helper fuctions for drawing basic shapes and objects
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef POINTER_H
#define POINTER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <shape.h>
#include <utils.h>
#include <mesh.h>
#include <symbol.h>
#include <sentence.h>

const uint16_t LED_PIN = 5;
const uint32_t I2C_CLOCK = 1000000;

class Pointer
{
private:
    // References to the x and y galvo outputs
    // Accepts voltage values from (0-4095)

    Adafruit_MCP4725 xdim;
    Adafruit_MCP4725 ydim;

protected:
    Pointer();

public:
    /**
     * @brief Points the laser to the provided position, pos
     * 0,0 is the bottom left of the screen
     * 4095,4095 is the top left of the screen
     * WIDTH/2, HEIGHT/2 is the middle of the screen
     *
     * @param pos
     */
    void point_to(Point2D pos);

    /**
     * @brief Moves the pointer towards the provided pos at a given speed, helpful if you want
     * longer and exagurated lines
     *
     * @param pos
     */
    void move_towards(Point2D pos, uint16_t delay_time);
    // Toggles the state of the LED
    void toggle_led();
    // Sets the state of the led to state
    // Ex. HIGH -> on
    // LOW -> Off
    void toggle_led(int8_t state);

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
    void draw_mesh(Mesh m);
    void draw_symbol(Symbol s, bool first_word);
    void draw_sentence(Sentence sen);

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
/**
 * @brief Draws a given shape s
 *
 * @param s
 */
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

void Pointer::move_towards(Point2D pos, uint16_t delay_time)
{
    int16_t xstep = (pos.x - cur_pos.x) >= 0 ? 1 : -1;
    int16_t ystep = (pos.y - cur_pos.y) >= 0 ? 1 : -1;
    int16_t newx = cur_pos.x;
    int16_t newy = cur_pos.y;

    while (cur_pos.x != pos.x || cur_pos.y != pos.y)
    {
        if (cur_pos.x != pos.x)
        {
            newx += xstep;
        }
        if (cur_pos.y != pos.y)
        {
            newy += ystep;
        }

        point_to({newx, newy});
        delay(delay_time);
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

        uint16_t xmin = c.t.pos.x - c.t.scale.x;
        uint16_t xmax = c.t.pos.x + c.t.scale.x;
        uint16_t ymin = c.t.pos.y - c.t.scale.y;
        uint16_t ymax = c.t.pos.y + c.t.scale.y;

        Point2D new_pos = {(uint16_t)normalize(sin(val), -1, 1, xmin, xmax), (uint16_t)normalize(cos(val), -1, 1, ymin, ymax)};
        // Serial.println(new_pos.y);
        point_to(new_pos);
    }
    toggle_led();
}

void Pointer::draw_rect(Shape s)
{
    uint16_t leftbound = s.t.pos.x - s.t.scale.x;
    uint16_t rightbound = s.t.pos.x + s.t.scale.x;
    uint16_t bottombound = s.t.pos.y - s.t.scale.y;
    uint16_t topbound = s.t.pos.y + s.t.scale.y;

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
            u_int16_t newx = (WIDTH / 2) + (g.s.t.scale.x * 2 * i);
            u_int16_t newy = (HEIGHT / 2) + (g.s.t.scale.y * 2 * j);
            g.s.t.pos = {newx, newy};
            draw_shape(g.s);
        }
    }
}

void Pointer::draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols)
{
    struct Point3D vertex[8] = {{-1, 1, -1}, {1, 1, -1}, {-1, -1, -1}, {1, -1, -1}, {-1, 1, 1}, {1, 1, 1}, {-1, -1, 1}, {1, -1, 1}};
}

void Pointer::draw_mesh(Mesh m)
{
    Vec2 newpos;
    // delay(1000);
    for (int i = 0; i < m.travel_order.size(); i++)
    {
        newpos = normalize(m.verticies[m.travel_order[i]], -1, 1, 0, 1000);
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
    for (int i = 0; i < s.m.travel_order.size(); i++)
    {
        newpos.x = normalize(s.m.verticies[s.m.travel_order[i]].x, -1, 1, 0, s.t.scale.x) + s.t.pos.x;
        newpos.y = normalize(s.m.verticies[s.m.travel_order[i]].y, -1, 1, 0, s.t.scale.y) + s.t.pos.y;
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

    Transform t({sen.font_size, sen.font_size}, newPos);
    Symbol sym = sen.word[0];
    sym.t = t;
    Serial.println("drawing a letter");
    draw_symbol(sym, true);
    for (int i = 1; i < sent_size; i++)
    {
        newPos = {newPos.x + sen.kernaling, newPos.y};
        if (newPos.x + sen.kernaling >= WIDTH)
        {
            line_count++;
            newPos = {sen.t.pos.x, newPos.y - sen.font_size * 2};
        }
        Transform t({sen.font_size, sen.font_size}, newPos);
        Symbol sym = sen.word[i];
        sym.t = t;
        Serial.println("drawing a letter");
        draw_symbol(sym, false);
        // delay(500);
    }
    toggle_led(LOW);
}
#endif