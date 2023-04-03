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
// #include <shape.h>
// #include <sentence.h>
// #include <screen.h>
// #include <pong.h>
// #include <demos/balls.h>
// #include <demos/rotatingcube.h>
// #include <demos/cube3d.h>

// // Global variables
// Graphic *cubeg = new Shape(Shape::Rectangle);
// GameObject2D *cube = (new GameObject2D(cubeg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({1000, 1000})->setColor(RED);

// Pointer &p = Pointer::getInstance();
// std::string message = "123456789101112131415";
// Pong pong_game;
// Demo *demo;

// Sentence sen(message); // kernaling, fontsize

// void setup(void)
// {
//     Serial.begin(9600);
//     Serial.println("Hello!");
//     delay(2000);
//     demo = new BallDemo();

//     p.init();

//     pong_game.init();
//     // demo->init();
//     // demo->setSpeed(0.5);
// }

// int16_t delay_cycle = 10000;
// u_int32_t delay_var = 1500;

// void loop(void)
// {
//     // demo->update();
//     // demo->draw();
//     // delay(500);

//     // p.drawILDA(ild);
//     pong_game.draw();
//     pong_game.update();
// }
