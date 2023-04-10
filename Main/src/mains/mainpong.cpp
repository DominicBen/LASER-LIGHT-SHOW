// /**************************************************************************/
// /*!
//     @file     trianglewave.pde
//     @author   Adafruit Industries
//     @license  BSD (see license.txt)

//     This example will generate a triangle wave with the MCP4725 DAC.

//     This is an example sketch for the Adafruit MCP4725 breakout board
//     ----> http://www.adafruit.com/products/935

//     Adafruit invests time and resources providing this open source code,
//     please support Adafruit and open-source hardware by purchasing
//     products from Adafruit!
// */
// /**************************************************************************/
// #include <Arduino.h>
// #include "TeensyDebug.h"
// #include <Wire.h>
// #include <Adafruit_MCP4725.h>
// #include <vector>

// #pragma GCC optimize("O0")
// // Custom Libraries

// #include <pointer.h>
// #include <graphics/shape.h>
// #include <graphics/sentence.h>
// #include <pong.h>

// // Global variables

// Pointer &p = Pointer::getInstance();
// Pong pong_game;

// void setup(void)
// {
//     Serial.begin(9600);
//     Serial.println("Hello!");
//     delay(2000);

//     p.init();

//     pong_game.init();
// }

// int16_t delay_cycle = 10000;
// u_int32_t delay_var = 1500;

// void loop(void)
// {
//     pong_game.draw();
//     pong_game.update();
// }
