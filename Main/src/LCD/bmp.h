#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h> // Core graphics library
#include <SPI.h>
#include <Wire.h>
#include <SD.h>

#include <LCD/screenwrapper.h>

#define BUFFPIXEL 20

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f);

uint32_t read32(File f);

uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

byte decToBcd(byte val);

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

void bmpDraw(const char *filename, int x, int y);