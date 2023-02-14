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
#include <BasicLinearAlgebra.h>

// Custom Libraries

#include <pointer.h>
#include <utils.h>
#include <point.h>
#include <shape.h>

// Global variables

Pointer &p = Pointer::getInstance();
Transform trans;
Shape s;
Shape c;
Grid g;
Mesh m('k');
Symbol sm(m);
std::string message = "i am a danger   to society";
Sentence sen(message, 250, 400);

void setup(void)
{

  Serial.begin(9600);
  Serial.println("Hello!");

  trans = Transform();
  s = Shape(Shape::Square, 400, trans);
  trans.scale = {400, 100};
  c = Shape(Shape::Circle, 50, trans);
  g = Grid(c);

  sm.t = Transform({1000, 1000});
  sen.t.pos = {400, HEIGHT - 800};
  p.toggle_led();
}

// Circle c = {WIDTH / 2 - 500, HEIGHT / 2 + 66, 100, 100, 200};

int16_t delay_cycle = 100;
int16_t delay_var = 500;

void loop(void)
{

  // Serial.println("Hello");

  // p.draw_shape(c);
  // p.draw_shape(s);

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

  // p.point_to({0, 0});
  // delayMicroseconds(delay_var);
  // p.point_to({4095, 4095});
  // delay(delay_cycle);

  // delay(200);
  // p.draw_symbol(sm);
  p.draw_sentence(sen);
  // p.draw_sentence(sen);
}