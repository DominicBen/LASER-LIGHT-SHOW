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
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 xdim;
Adafruit_MCP4725 ydim;

uint16_t slowness = 0 ;
uint16_t cycle_delay = 1000;
uint16_t r = 1000;
uint16_t counter = 0;
uint16_t res = 150;

// TWBR = 12; // 400 khz

void setup(void) {
  Wire1.setClock(1000000);
  Serial.begin(9600);
  Serial.println("Hello!");
  dsds dd =dd d=ds=ds
  sd


  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  xdim.begin(0x63);
  ydim.begin(0x62);
    
  Serial.println("Generating a triangle wave");
}

uint32_t clamp(uint32_t n, uint32_t min, uint32_t max)
{
  if (n > max) { return max;}
  else if (n < min) { return min;}
  else { return n;}
}

double normalize(double old_value, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
{
  double new_value = ( (old_value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
  return new_value;
}




void draw_circle(double slowness, uint32_t radius, uint32_t x, uint32_t y)
{
  uint32_t counter;
  for (counter = 0; counter < 360 * slowness; counter++)
    {
      // Serial.println(normalize(sin(counter/slowness),-1,1,0,4095));
      uint16_t xmin = x-radius;
      uint16_t xmax = x+radius;
      uint16_t ymin = y-radius;
      uint16_t ymax = y+radius;
      uint16_t tempx = clamp(normalize(sin(counter/slowness),-1,1,xmin, xmax),0,4095);
      uint16_t tempy = clamp(normalize(cos(counter/slowness),-1,1,ymin,ymax),0,4095);
      xdim.setVoltage(tempx, false);
      ydim.setVoltage(tempy, false);
    }
}

void loop(void) {

    delay(slowness);

    double val = ((2 * PI) / res) * counter;
    uint16_t newx = normalize(sin(val),-1,1,2048 - r,2048 + r);
    uint16_t newy = normalize(cos(val),-1,1,2048 - r,2048 + r);
      
      
    xdim.setVoltage(newx, false);
    ydim.setVoltage(newy, false);

    if (counter >= res) { counter = 0; delay(cycle_delay);}
    else { counter++;}

  
}