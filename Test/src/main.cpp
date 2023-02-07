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
#include <Pointer.h>
#include <Utils.h>
#include <Point.h>
#include <Shape.h>

Pointer &p = Pointer::getInstance();

void setup(void)
{

  Serial.begin(9600);
  Serial.println("Hello!");
}

// Circle c = {WIDTH / 2 - 500, HEIGHT / 2 + 66, 100, 100, 200};
Shape s = Shape(Shape::Square, 400, 200, 200);
Shape c = Shape(Shape::Circle, 50, 400, 200);

Grid g = Grid(c);

void loop(void)
{

  // Serial.println("Hello");

  // p.draw_shape(c);
  // p.draw_shape(s);

  p.draw_grid(c);
}