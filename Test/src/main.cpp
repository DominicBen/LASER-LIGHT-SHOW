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
#include <Pointer.h>
#include <Utils.h>
#include <Point.h>
#include <Shape.h>

Adafruit_MCP4725 xdim;
Adafruit_MCP4725 ydim;

Pointer &p = Pointer::getInstance();

// const uint16_t WIDTH = 4096;
// const uint16_t HEIGHT = 4096;
// const uint16_t DEPTH = 100;
// const uint32_t I2C_CLOCK = 1000000;

uint16_t slowness = 100;
uint16_t cycle_delay = 1000;
uint16_t r = 1000;
uint16_t counter = 0;

// TWBR = 12; // 400 khz

// X and Y position between 0-4095
struct Circle
{
  uint16_t x;
  uint16_t y;
  int16_t x_vel;
  int16_t y_vel;
  uint16_t radius;
};

void setup(void)
{

  Serial.begin(9600);
  Serial.println("Hello!");

  pinMode(5, OUTPUT);

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  xdim.begin(0x63);
  ydim.begin(0x62);

  Serial.println("Generating a triangle wave");
}
// template <typename T>
// T clamp(T n, T min, T max)
// {
//   if (n > max)
//   {
//     return max;
//   }
//   else if (n < min)
//   {
//     return min;
//   }
//   else
//   {
//     return n;
//   }
// }

// double normalize(double old_value, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
// {
//   double new_value = ((old_value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
//   return new_value;
// }

// void draw_circle(double res, Circle c)
// {
//   uint32_t counter;
//   for (counter = 0; counter < res * 2; counter++)
//   {
//     // Serial.println(normalize(sin(counter/slowness),-1,1,0,4095));
//     double val = ((2 * PI) / res) * counter;

//     uint16_t xmin = c.x - c.radius;
//     uint16_t xmax = c.x + c.radius;
//     uint16_t ymin = c.y - c.radius;
//     uint16_t ymax = c.y + c.radius;

//     uint16_t tempx = clamp<uint16_t>(normalize(sin(val), -1, 1, xmin, xmax), 0, 4095);
//     uint16_t tempy = clamp<uint16_t>(normalize(cos(val), -1, 1, ymin, ymax), 0, 4095);

//     xdim.setVoltage(tempx, false, I2C_CLOCK);
//     ydim.setVoltage(tempy, false, I2C_CLOCK);
//   }
// }

// void draw_square(double res, uint32_t size, uint32_t x, uint32_t y)
// {
//   uint16_t leftbound = x - size;
//   uint16_t rightbound = x + size;
//   uint16_t bottombound = y - size;
//   uint16_t topbound = y + size;

//   xdim.setVoltage(leftbound, false, I2C_CLOCK);
//   ydim.setVoltage(bottombound, false, I2C_CLOCK);

//   delayMicroseconds(res);
//   digitalWrite(5, HIGH);

//   xdim.setVoltage(leftbound, false, I2C_CLOCK);
//   ydim.setVoltage(topbound, false, I2C_CLOCK);

//   delayMicroseconds(res);

//   xdim.setVoltage(rightbound, false, I2C_CLOCK);
//   ydim.setVoltage(topbound, false, I2C_CLOCK);

//   delayMicroseconds(res);

//   xdim.setVoltage(rightbound, false, I2C_CLOCK);
//   ydim.setVoltage(bottombound, false, I2C_CLOCK);

//   delayMicroseconds(res);

//   xdim.setVoltage(leftbound, false, I2C_CLOCK);
//   ydim.setVoltage(bottombound, false, I2C_CLOCK);
//   delayMicroseconds(res);
//   digitalWrite(5, LOW);
// }

// void draw_grid(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols)
// {
//   for (int32_t i = -cols / 2; i <= cols / 2; i++)
//   {
//     for (int32_t j = -rows / 2; j <= rows / 2; j++)
//     {

//       draw_square(350, size, WIDTH / 2 + (size * 2 * i), HEIGHT / 2 + (size * 2 * j));
//     }
//   }
// }

// Circle c = {WIDTH / 2 - 500, HEIGHT / 2 + 66, 100, 100, 200};
Shape c = Shape(Shape::Circle, 500, 500);

void loop(void)
{
  // Serial.println("Hello");

  p.draw_circle(c);
}