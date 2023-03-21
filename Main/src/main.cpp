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
// #include <ILDA.h>
// #include <shape.h>
#include <shape.h>

#include <screen.h>

// #include <pong.h>

static const char *files[] = {
    "ilda/cube.ild",    // works
    "ilda/money.ild",   // kinda work
    "ilda/wall.ild",    // doesnt work
    "ilda/tunnel.ild",  // doesnt work
    "ilda/nasa.ild",    // doesnt work
    "ilda/magic.ild",   // doesnt wark
    "ilda/wheel.ild",   // doesnt work
    "ilda/tunnel2.ild", // doesnt work
    "ilda/land.ild",    // doesnt work
};
static const int num_files = 9;

// Global variables
Graphic *g = &Shape(Shape::Circle).setPosition({WIDTH / 2, HEIGHT / 2});

Pointer &p = Pointer::getInstance();
// Transform2D trans;
// Shape s;
// Shape c;
// Grid g;
// Mesh m('k');
// Char sm(m);
// std::string message = "123456789101112131415";
// Pong pong_game;

// Sentence sen(message); // kernaling, fontsize
// Screen screen;

// ILDA ild;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");

  p.format_info.kerneling = 350;
  p.format_info.font_size = 500;

  // trans = Transform2D();
  // s = Shape(Shape::Square, trans);

  // c = Shape(Shape::Circle, trans);
  // c.transform.scale = {100, 100};
  // g = Grid(c);
  // g.rows = 5;
  // g.cols = 5;

  // sm.transform = Transform2D(Vec2{1000, 1000});
  // sen.transform.pos = {400, HEIGHT - 800};
  // p.toggleLed(HIGH);
  // ild.read(files[0]);
  // pong_game.init();
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
  g->draw();
  // Serial.println("Hello");
  // Timing Library

  // p.drawShape(s);
  // p.draw_shape(c);
  // p.drawGrid(g);

  // p.pointTo({0, 0});
  // // delayMicroseconds(delay_var);
  // p.pointTo({0, 4095});
  // // delayMicroseconds(delay_var);
  // p.pointTo({4095, 4095});
  // // delayMicroseconds(delay_var);
  // p.pointTo({4095, 0});
  // // delayMicroseconds(delay_var);
  // p.pointTo({0, 0});
  // // delay(delay_cycle);
  // p.drawRect(WIDTH / 2, HEIGHT / 2, 4095, 4095);

  // p.point_to(Vec2{0, 0});
  // delayMicroseconds(delay_var);
  // p.point_to(Vec2{4095, 4095});
  // delay(delay_cycle);

  // delay(200);
  // p.draw_symbol(sm);
  // p.print(sen);
  // p.pointTo({WIDTH / 2, HEIGHT - 200});

  // delay(20);

  // p.point_to({0, 0});
  // // delayMicroseconds(delay_var);
  // p.point_to({0, HEIGHT - 1});
  // // delayMicroseconds(delay_var);
  // p.point_to({WIDTH - 1, HEIGHT - 1});
  // // delayMicroseconds(delay_var);
  // p.point_to({WIDTH - 1, 0});
  // // delayMicroseconds(delay_var);

  // p.drawILDA(ild);
  // pong_game.update();
  // pong_game.draw();
  // p.format_info.cursor_pos = {100, 3000};
  // p.print("player ");
  // p.print("0");

  // p.println("winner");
  // delay(1000);
  // exit(0);
}
