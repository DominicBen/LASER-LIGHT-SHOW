/**************************************************************************/
/*!
    @file     trianglewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a triangle wave with the MCP4725 DAC.

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <vector>

// Custom Libraries

#include <pointer.h>
#include <utils.h>
#include <point.h>
#include <shape.h>
#include <screen.h>

// Global variables

Pointer &p = Pointer::getInstance();
Transform2D trans;
Shape s;
Shape c;
Grid g;
Mesh m('k');
Symbol sm(m);
std::string message = "hello world";

Sentence sen(message, 350, 500); // kernaling, fontsize
Screen screen;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");

  trans = Transform2D();
  s = Shape(Shape::Square, 400, trans);

  c = Shape(Shape::Circle, 500, trans);
  c.t.scale = {100, 100};
  s.res = 300;
  g = Grid(s);
  g.rows = 10;
  g.cols = 10;

  sm.t = Transform2D(Vec2{1000, 1000});
  sen.t.pos = {400, HEIGHT - 800};
  p.toggle_led(HIGH);
}

// Circle c = {WIDTH / 2 - 500, HEIGHT / 2 + 66, 100, 100, 200};

// 1300 MicroSeconds for Low Resolution
// 1350 Medium resolution
// 1400 Medium- High
// 1450 High, Dots appear
// 1500 Highest, Dots appear

int16_t delay_cycle = 100;
u_int32_t delay_var = 1500;

void loop(void)
{
  // Serial.println("Hello");
  // Timing Library
  // p.draw_shape(c);
  // p.draw_shape(c);
  // p.draw_grid(g);

  // p.point_to({0, 0});
  // delayMicroseconds(delay_var);
  // p.point_to({0, 4095});
  // delayMicroseconds(delay_var);
  // p.point_to({4095, 4095});
  // delayMicroseconds(delay_var);
  // p.point_to({4095, 0});
  // delayMicroseconds(delay_var);
  // p.point_to({0, 0});
  // delay(delay_cycle);

  // p.point_to(Vec2{0, 0});
  // delayMicroseconds(delay_var);
  // p.point_to(Vec2{4095, 4095});
  // delay(delay_cycle);

  // delay(200);
  // p.draw_symbol(sm);
  // p.draw_sentence(sen);
  // delay(20);

  p.point_to({0, 0});
  // delayMicroseconds(delay_var);
  p.point_to({0, HEIGHT - 1});
  // delayMicroseconds(delay_var);
  p.point_to({WIDTH - 1, HEIGHT - 1});
  // delayMicroseconds(delay_var);
  p.point_to({WIDTH - 1, 0});
  // delayMicroseconds(delay_var);
}