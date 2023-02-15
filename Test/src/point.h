#ifndef POINT_H
#define POINT_H

// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_MCP4725.h>

// const uint16_t DEPTH = 100;
// const uint16_t WIDTH = 4096;
// const uint16_t HEIGHT = 4096;

// class Point3D
// {
// private:
//   /* data */
// public:
//   int16_t x = 0;
//   int16_t y = 0;
//   int16_t z = 0;

//   int16_t scale_proj = 0;
//   int16_t x_proj = 0;
//   int16_t y_proj = 0;

//   void update();
//   Point3D(int16_t x_, int16_t y_, int16_t z_);
//   ~Point3D();
// };

// void Point3D::update(/* args */)
// {
//   scale_proj = DEPTH / (DEPTH + z);
//   x_proj = (x * scale_proj) + WIDTH / 2;
//   y_proj = (y * scale_proj) + HEIGHT / 2;
// }

// Point3D::Point3D(int16_t x_, int16_t y_, int16_t z_)
// {
//   x = x_;
//   y = y_;
//   z = z_;
// }

// Point3D::~Point3D()
// {
// }

#endif