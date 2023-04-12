/**************************************************************************/
/*!
    @file     Adafruit_RA8875.cpp
    @author   Limor Friend/Ladyada, K.Townsend/KTOWN for Adafruit Industries
    @license  BSD license, all text above and below must be included in
              any redistribution

 This is the library for the Adafruit RA8875 Driver board for TFT displays
 ---------------> http://www.adafruit.com/products/1590
 The RA8875 is a TFT driver for up to 800x480 dotclock'd displays
 It is tested to work with displays in the Adafruit shop. Other displays
 may need timing adjustments and are not guanteed to work.
 
 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!
 
 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.

    @section  HISTORY
    
    v1.0 - First release
*/
/**************************************************************************/
#include "mbed.h"
#include "Adafruit_RA8875.h"

/**************************************************************************/
/*!
      Constructor for a new RA8875 instance
      
      @args CS[in]  Location of the SPI chip select pin
      @args RST[in] Location of the reset pin
*/
/**************************************************************************/
Adafruit_RA8875::Adafruit_RA8875(PinName CS, PinName RST, SPI* TFT_SPI) : Adafruit_GFX(800, 480), _cs(CS), _rst(RST)
{
    _spi = TFT_SPI;
}

/**************************************************************************/
/*!
      Initialises the LCD driver and any HW required by the display
      
      @args s[in] The display size, which can be either:
                  'RA8875_480x272' (4.3" displays) r
                  'RA8875_800x480' (5" and 7" displays)
*/
/**************************************************************************/
bool Adafruit_RA8875::begin(enum RA8875sizes s) {
  _size = s;

    switch (_size)
    {
        case RA8875_480x272:
            _width = 480;
            _height = 272;
            break;
        case RA8875_800x480:
            _width = 800;
            _height = 480;
            break;
    }

  _cs=1;
  _rst=0;
  wait_ms(100);
  _rst=1;
  wait_ms(100);
  
/*  _spibegin();
#ifdef __AVR__
  _spisetClockDivider(SPI_CLOCK_DIV128);
  _spisetDataMode(SPI_MODE0);
#endif*/
  
  if (readReg(0) != 0x75) {
    return false;
  }

  initialize();
/*
#ifdef __AVR__
  _spisetClockDivider(SPI_CLOCK_DIV4);
#endif*/
  return true;
}

/************************* Initialization *********************************/

/**************************************************************************/
/*!
      Performs a SW-based reset of the RA8875
*/
/**************************************************************************/
void Adafruit_RA8875::softReset(void) {
  writeCommand(RA8875_PWRR);
  writeData(RA8875_PWRR_SOFTRESET);
  writeData(RA8875_PWRR_NORMAL);
  wait_ms(1);
}

/**************************************************************************/
/*!
      Initialise the PLL
*/
/**************************************************************************/
void Adafruit_RA8875::PLLinit(void) {
  switch (_size)
  {
    case RA8875_480x272:
        writeReg(RA8875_PLLC1, RA8875_PLLC1_PLLDIV1 + 10);
        wait_ms(1);
        writeReg(RA8875_PLLC2, RA8875_PLLC2_DIV4);
        wait_ms(1);
        break;
    case RA8875_800x480:
        writeReg(RA8875_PLLC1, RA8875_PLLC1_PLLDIV1 + 10);
        wait_ms(1);
        writeReg(RA8875_PLLC2, RA8875_PLLC2_DIV4);
        wait_ms(1);
        break;
  }
}

/**************************************************************************/
/*!
      Initialises the driver IC (clock setup, etc.)
*/
/**************************************************************************/
void Adafruit_RA8875::initialize(void) {
  PLLinit();
  writeReg(RA8875_SYSR, RA8875_SYSR_16BPP | RA8875_SYSR_MCU8);

  /* Timing values */
  uint8_t pixclk;
  uint8_t hsync_start;
  uint8_t hsync_pw;
  uint8_t hsync_finetune;
  uint8_t hsync_nondisp;
  uint8_t vsync_pw; 
  uint16_t vsync_nondisp;
  uint16_t vsync_start;

  /* Set the correct values for the display being used */  
  switch (_size)
  {
      case RA8875_480x272: 
        pixclk          = RA8875_PCSR_PDATL | RA8875_PCSR_4CLK;
        hsync_nondisp   = 10;
        hsync_start     = 8;
        hsync_pw        = 48;
        hsync_finetune  = 0;
        vsync_nondisp   = 3;
        vsync_start     = 8;
        vsync_pw        = 10;
        break; 
    case RA8875_800x480:
        pixclk          = RA8875_PCSR_PDATL | RA8875_PCSR_2CLK;
        hsync_nondisp   = 26;
        hsync_start     = 32;
        hsync_pw        = 96;
        hsync_finetune  = 0;
        vsync_nondisp   = 32;
        vsync_start     = 23;
        vsync_pw        = 2;
        break;
  }

  writeReg(RA8875_PCSR, pixclk);
  wait_ms(1);
  
  /* Horizontal settings registers */
  writeReg(RA8875_HDWR, (_width / 8) - 1);                          // H width: (HDWR + 1) * 8 = 480
  writeReg(RA8875_HNDFTR, RA8875_HNDFTR_DE_HIGH + hsync_finetune);
  writeReg(RA8875_HNDR, (hsync_nondisp - hsync_finetune - 2)/8);    // H non-display: HNDR * 8 + HNDFTR + 2 = 10
  writeReg(RA8875_HSTR, hsync_start/8 - 1);                         // Hsync start: (HSTR + 1)*8 
  writeReg(RA8875_HPWR, RA8875_HPWR_LOW + (hsync_pw/8 - 1));        // HSync pulse width = (HPWR+1) * 8
  
  /* Vertical settings registers */
  writeReg(RA8875_VDHR0, (uint16_t)(_height - 1) & 0xFF);
  writeReg(RA8875_VDHR1, (uint16_t)(_height - 1) >> 8);
  writeReg(RA8875_VNDR0, vsync_nondisp-1);                          // V non-display period = VNDR + 1
  writeReg(RA8875_VNDR1, vsync_nondisp >> 8);
  writeReg(RA8875_VSTR0, vsync_start-1);                            // Vsync start position = VSTR + 1
  writeReg(RA8875_VSTR1, vsync_start >> 8);
  writeReg(RA8875_VPWR, RA8875_VPWR_LOW + vsync_pw - 1);            // Vsync pulse width = VPWR + 1
  
  /* Set active window X */
  writeReg(RA8875_HSAW0, 0);                                        // horizontal start point
  writeReg(RA8875_HSAW1, 0);
  writeReg(RA8875_HEAW0, (uint16_t)(_width - 1) & 0xFF);            // horizontal end point
  writeReg(RA8875_HEAW1, (uint16_t)(_width - 1) >> 8);
  
  /* Set active window Y */
  writeReg(RA8875_VSAW0, 0);                                        // vertical start point
  writeReg(RA8875_VSAW1, 0);  
  writeReg(RA8875_VEAW0, (uint16_t)(_height - 1) & 0xFF);           // horizontal end point
  writeReg(RA8875_VEAW1, (uint16_t)(_height - 1) >> 8);
  
  /* ToDo: Setup touch panel? */
  
  /* Clear the entire window */
  writeReg(RA8875_MCLR, RA8875_MCLR_START | RA8875_MCLR_FULL);
  wait_ms(500); 
}

/**************************************************************************/
/*!
      Returns the display width in pixels
      
      @returns  The 1-based display width in pixels
*/
/**************************************************************************/
uint16_t Adafruit_RA8875::width(void) { return _width; }

/**************************************************************************/
/*!
      Returns the display height in pixels

      @returns  The 1-based display height in pixels
*/
/**************************************************************************/
uint16_t Adafruit_RA8875::height(void) { return _height; }

/************************* Text Mode ***********************************/

/**************************************************************************/
/*!
      Sets the display in text mode (as opposed to graphics mode)
*/
/**************************************************************************/
void Adafruit_RA8875::textMode(void) 
{
  /* Set text mode */
  writeCommand(RA8875_MWCR0);
  uint8_t temp = readData();
  temp |= RA8875_MWCR0_TXTMODE; // Set bit 7
  writeData(temp);
  
  /* Select the internal (ROM) font */
  writeCommand(0x21);
  temp = readData();
  temp &= ~((1<<7) | (1<<5)); // Clear bits 7 and 5
  writeData(temp);
}

/**************************************************************************/
/*!
      Sets the display in text mode (as opposed to graphics mode)
      
      @args x[in] The x position of the cursor (in pixels, 0..1023)
      @args y[in] The y position of the cursor (in pixels, 0..511)
*/
/**************************************************************************/
void Adafruit_RA8875::textSetCursor(uint16_t x, uint16_t y) 
{
  /* Set cursor location */
  writeCommand(0x2A);
  writeData(x & 0xFF);
  writeCommand(0x2B);
  writeData(x >> 8);
  writeCommand(0x2C);
  writeData(y & 0xFF);
  writeCommand(0x2D);
  writeData(y >> 8);
}

/**************************************************************************/
/*!
      Sets the fore and background color when rendering text
      
      @args foreColor[in] The RGB565 color to use when rendering the text
      @args bgColor[in]   The RGB565 colot to use for the background
*/
/**************************************************************************/
void Adafruit_RA8875::textColor(uint16_t foreColor, uint16_t bgColor)
{
  /* Set Fore Color */
  writeCommand(0x63);
  writeData((foreColor & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((foreColor & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((foreColor & 0x001f));
  
  /* Set Background Color */
  writeCommand(0x60);
  writeData((bgColor & 0xf800) >> 11);
  writeCommand(0x61);
  writeData((bgColor & 0x07e0) >> 5);
  writeCommand(0x62);
  writeData((bgColor & 0x001f));
  
  /* Clear transparency flag */
  writeCommand(0x22);
  uint8_t temp = readData();
  temp &= ~(1<<6); // Clear bit 6
  writeData(temp);
}

/**************************************************************************/
/*!
      Sets the fore color when rendering text with a transparent bg
      
      @args foreColor[in] The RGB565 color to use when rendering the text
*/
/**************************************************************************/
void Adafruit_RA8875::textTransparent(uint16_t foreColor)
{
  /* Set Fore Color */
  writeCommand(0x63);
  writeData((foreColor & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((foreColor & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((foreColor & 0x001f));

  /* Set transparency flag */
  writeCommand(0x22);
  uint8_t temp = readData();
  temp |= (1<<6); // Set bit 6
  writeData(temp);  
}

/**************************************************************************/
/*!
      Sets the text enlarge settings, using one of the following values:
      
      0 = 1x zoom
      1 = 2x zoom
      2 = 3x zoom
      3 = 4x zoom
      
      @args scale[in]   The zoom factor (0..3 for 1-4x zoom)
*/
/**************************************************************************/
void Adafruit_RA8875::textEnlarge(uint8_t scale)
{
  if (scale > 3) scale = 3;

  /* Set font size flags */
  writeCommand(0x22);
  uint8_t temp = readData();
  temp &= ~(0xF); // Clears bits 0..3
  temp |= scale << 2;
  temp |= scale;
  writeData(temp);  

  _textScale = scale;
}

/**************************************************************************/
/*!
      Renders some text on the screen when in text mode
      
      @args buffer[in]    The buffer containing the characters to render
      @args len[in]       The size of the buffer in bytes
*/
/**************************************************************************/
void Adafruit_RA8875::textWrite(const char* buffer, uint16_t len) 
{
  if (len == 0) len = strlen(buffer);
  writeCommand(RA8875_MRWC);
  for (uint16_t i=0;i<len;i++)
  {
    writeData(buffer[i]);
#if defined(__AVR__)
    if (_textScale > 1) wait_ms(1);
#elif defined(__arm__)
    // This delay is needed with textEnlarge(1) because
    // Teensy 3.X is much faster than Arduino Uno
    if (_textScale > 0) wait_ms(1);
#endif
  }
}

/************************* Graphics ***********************************/

/**************************************************************************/
/*!
      Sets the display in graphics mode (as opposed to text mode)
*/
/**************************************************************************/
void Adafruit_RA8875::graphicsMode(void) {
  writeCommand(RA8875_MWCR0);
  uint8_t temp = readData();
  temp &= ~RA8875_MWCR0_TXTMODE; // bit #7
  writeData(temp);
}

/**************************************************************************/
/*!
      Waits for screen to finish by polling the status!
*/
/**************************************************************************/
bool Adafruit_RA8875::waitPoll(uint8_t regname, uint8_t waitflag) {
  /* Wait for the command to finish */
  while (1)
  {
    uint8_t temp = readReg(regname);
    if (!(temp & waitflag))
      return true;
  }  
  return false; // MEMEFIX: yeah i know, unreached! - add timeout?
}


/**************************************************************************/
/*!
      Sets the current X/Y position on the display before drawing
      
      @args x[in] The 0-based x location
      @args y[in] The 0-base y location
*/
/**************************************************************************/
void Adafruit_RA8875::setXY(uint16_t x, uint16_t y) {
  writeReg(RA8875_CURH0, x);
  writeReg(RA8875_CURH1, x >> 8);
  writeReg(RA8875_CURV0, y);
  writeReg(RA8875_CURV1, y >> 8);  
}

/**************************************************************************/
/*!
      HW accelerated function to push a chunk of raw pixel data
      
      @args num[in] The number of pixels to push
      @args p[in]   The pixel color to use
*/
/**************************************************************************/
void Adafruit_RA8875::pushPixels(uint32_t num, uint16_t p) {
  _cs = 0;
  _spi->write(RA8875_DATAWRITE);
  while (num--) {
    _spi->write(p >> 8);
    _spi->write(p);
  }
  _cs = 1;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::fillRect(void) {
  writeCommand(RA8875_DCR);
  writeData(RA8875_DCR_LINESQUTRI_STOP | RA8875_DCR_DRAWSQUARE);
  writeData(RA8875_DCR_LINESQUTRI_START | RA8875_DCR_FILL | RA8875_DCR_DRAWSQUARE);
}

/**************************************************************************/
/*!
      Draws a single pixel at the specified location

      @args x[in]     The 0-based x location
      @args y[in]     The 0-base y location
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  writeReg(RA8875_CURH0, x);
  writeReg(RA8875_CURH1, x >> 8);
  writeReg(RA8875_CURV0, y);
  writeReg(RA8875_CURV1, y >> 8);  
  writeCommand(RA8875_MRWC);
  _cs = 0;
  _spi->write(RA8875_DATAWRITE);
  _spi->write(color >> 8);
  _spi->write(color);
  _cs = 1;
}

/**************************************************************************/
/*!
      Draws a HW accelerated line on the display
    
      @args x0[in]    The 0-based starting x location
      @args y0[in]    The 0-base starting y location
      @args x1[in]    The 0-based ending x location
      @args y1[in]    The 0-base ending y location
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
  /* Set X */
  writeCommand(0x91);
  writeData(x0);
  writeCommand(0x92);
  writeData(x0 >> 8);
  
  /* Set Y */
  writeCommand(0x93);
  writeData(y0); 
  writeCommand(0x94);
  writeData(y0 >> 8);
  
  /* Set X1 */
  writeCommand(0x95);
  writeData(x1);
  writeCommand(0x96);
  writeData((x1) >> 8);
  
  /* Set Y1 */
  writeCommand(0x97);
  writeData(y1); 
  writeCommand(0x98);
  writeData((y1) >> 8);
  
  /* Set Color */
  writeCommand(0x63);
  writeData((color & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((color & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((color & 0x001f));

  /* Draw! */
  writeCommand(RA8875_DCR);
  writeData(0x80);
  
  /* Wait for the command to finish */
  waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  drawLine(x, y, x, y+h, color);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  drawLine(x, y, x+w, y, color);
}

/**************************************************************************/
/*!
      Draws a HW accelerated rectangle on the display

      @args x[in]     The 0-based x location of the top-right corner
      @args y[in]     The 0-based y location of the top-right corner
      @args w[in]     The rectangle width
      @args h[in]     The rectangle height
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  rectHelper(x, y, x+w, y+h, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled rectangle on the display

      @args x[in]     The 0-based x location of the top-right corner
      @args y[in]     The 0-based y location of the top-right corner
      @args w[in]     The rectangle width
      @args h[in]     The rectangle height
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  rectHelper(x, y, x+w, y+h, color, true);
}

/**************************************************************************/
/*!
      Fills the screen with the spefied RGB565 color

      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillScreen(uint16_t color)
{  
  rectHelper(0, 0, _width-1, _height-1, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated circle on the display

      @args x[in]     The 0-based x location of the center of the circle
      @args y[in]     The 0-based y location of the center of the circle
      @args w[in]     The circle's radius
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  circleHelper(x0, y0, r, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled circle on the display

      @args x[in]     The 0-based x location of the center of the circle
      @args y[in]     The 0-based y location of the center of the circle
      @args w[in]     The circle's radius
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  circleHelper(x0, y0, r, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated triangle on the display

      @args x0[in]    The 0-based x location of point 0 on the triangle
      @args y0[in]    The 0-based y location of point 0 on the triangle
      @args x1[in]    The 0-based x location of point 1 on the triangle
      @args y1[in]    The 0-based y location of point 1 on the triangle
      @args x2[in]    The 0-based x location of point 2 on the triangle
      @args y2[in]    The 0-based y location of point 2 on the triangle
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  triangleHelper(x0, y0, x1, y1, x2, y2, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled triangle on the display

      @args x0[in]    The 0-based x location of point 0 on the triangle
      @args y0[in]    The 0-based y location of point 0 on the triangle
      @args x1[in]    The 0-based x location of point 1 on the triangle
      @args y1[in]    The 0-based y location of point 1 on the triangle
      @args x2[in]    The 0-based x location of point 2 on the triangle
      @args y2[in]    The 0-based y location of point 2 on the triangle
      @args color[in] The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  triangleHelper(x0, y0, x1, y1, x2, y2, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated ellipse on the display

      @args xCenter[in]   The 0-based x location of the ellipse's center
      @args yCenter[in]   The 0-based y location of the ellipse's center
      @args longAxis[in]  The size in pixels of the ellipse's long axis
      @args shortAxis[in] The size in pixels of the ellipse's short axis
      @args color[in]     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color)
{
  ellipseHelper(xCenter, yCenter, longAxis, shortAxis, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled ellipse on the display

      @args xCenter[in]   The 0-based x location of the ellipse's center
      @args yCenter[in]   The 0-based y location of the ellipse's center
      @args longAxis[in]  The size in pixels of the ellipse's long axis
      @args shortAxis[in] The size in pixels of the ellipse's short axis
      @args color[in]     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color)
{
  ellipseHelper(xCenter, yCenter, longAxis, shortAxis, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated curve on the display

      @args xCenter[in]   The 0-based x location of the ellipse's center
      @args yCenter[in]   The 0-based y location of the ellipse's center
      @args longAxis[in]  The size in pixels of the ellipse's long axis
      @args shortAxis[in] The size in pixels of the ellipse's short axis
      @args curvePart[in] The corner to draw, where in clock-wise motion:
                            0 = 180-270°
                            1 = 270-0°
                            2 = 0-90°
                            3 = 90-180°
      @args color[in]     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color)
{
  curveHelper(xCenter, yCenter, longAxis, shortAxis, curvePart, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled curve on the display

      @args xCenter[in]   The 0-based x location of the ellipse's center
      @args yCenter[in]   The 0-based y location of the ellipse's center
      @args longAxis[in]  The size in pixels of the ellipse's long axis
      @args shortAxis[in] The size in pixels of the ellipse's short axis
      @args curvePart[in] The corner to draw, where in clock-wise motion:
                            0 = 180-270°
                            1 = 270-0°
                            2 = 0-90°
                            3 = 90-180°
      @args color[in]     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color)
{
  curveHelper(xCenter, yCenter, longAxis, shortAxis, curvePart, color, true);
}

/**************************************************************************/
/*!
      Helper function for higher level circle drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::circleHelper(int16_t x0, int16_t y0, int16_t r, uint16_t color, bool filled)
{
  /* Set X */
  writeCommand(0x99);
  writeData(x0);
  writeCommand(0x9a);
  writeData(x0 >> 8);
  
  /* Set Y */
  writeCommand(0x9b);
  writeData(y0); 
  writeCommand(0x9c);      
  writeData(y0 >> 8);
  
  /* Set Radius */
  writeCommand(0x9d);
  writeData(r);  
  
  /* Set Color */
  writeCommand(0x63);
  writeData((color & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((color & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((color & 0x001f));
  
  /* Draw! */
  writeCommand(RA8875_DCR);
  if (filled)
  {
    writeData(RA8875_DCR_CIRCLE_START | RA8875_DCR_FILL);
  }
  else
  {
    writeData(RA8875_DCR_CIRCLE_START | RA8875_DCR_NOFILL);
  }
  
  /* Wait for the command to finish */
  waitPoll(RA8875_DCR, RA8875_DCR_CIRCLE_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level rectangle drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::rectHelper(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool filled)
{
  /* Set X */
  writeCommand(0x91);
  writeData(x);
  writeCommand(0x92);
  writeData(x >> 8);
  
  /* Set Y */
  writeCommand(0x93);
  writeData(y); 
  writeCommand(0x94);      
  writeData(y >> 8);
  
  /* Set X1 */
  writeCommand(0x95);
  writeData(w);
  writeCommand(0x96);
  writeData((w) >> 8);
  
  /* Set Y1 */
  writeCommand(0x97);
  writeData(h); 
  writeCommand(0x98);
  writeData((h) >> 8);

  /* Set Color */
  writeCommand(0x63);
  writeData((color & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((color & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((color & 0x001f));

  /* Draw! */
  writeCommand(RA8875_DCR);
  if (filled)
  {
    writeData(0xB0);
  }
  else
  {
    writeData(0x90);
  }
  
  /* Wait for the command to finish */
  waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level triangle drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::triangleHelper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, bool filled)
{
  /* Set Point 0 */
  writeCommand(0x91);
  writeData(x0);
  writeCommand(0x92);
  writeData(x0 >> 8);
  writeCommand(0x93);
  writeData(y0); 
  writeCommand(0x94);
  writeData(y0 >> 8);

  /* Set Point 1 */
  writeCommand(0x95);
  writeData(x1);
  writeCommand(0x96);
  writeData(x1 >> 8);
  writeCommand(0x97);
  writeData(y1); 
  writeCommand(0x98);
  writeData(y1 >> 8);

  /* Set Point 2 */
  writeCommand(0xA9);
  writeData(x2);
  writeCommand(0xAA);
  writeData(x2 >> 8);
  writeCommand(0xAB);
  writeData(y2); 
  writeCommand(0xAC);
  writeData(y2 >> 8);
  
  /* Set Color */
  writeCommand(0x63);
  writeData((color & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((color & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((color & 0x001f));
  
  /* Draw! */
  writeCommand(RA8875_DCR);
  if (filled)
  {
    writeData(0xA1);
  }
  else
  {
    writeData(0x81);
  }
  
  /* Wait for the command to finish */
  waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level ellipse drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::ellipseHelper(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color, bool filled)
{
  /* Set Center Point */
  writeCommand(0xA5);
  writeData(xCenter);
  writeCommand(0xA6);
  writeData(xCenter >> 8);
  writeCommand(0xA7);
  writeData(yCenter); 
  writeCommand(0xA8);
  writeData(yCenter >> 8);

  /* Set Long and Short Axis */
  writeCommand(0xA1);
  writeData(longAxis);
  writeCommand(0xA2);
  writeData(longAxis >> 8);
  writeCommand(0xA3);
  writeData(shortAxis); 
  writeCommand(0xA4);
  writeData(shortAxis >> 8);
  
  /* Set Color */
  writeCommand(0x63);
  writeData((color & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((color & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((color & 0x001f));
  
  /* Draw! */
  writeCommand(0xA0);
  if (filled)
  {
    writeData(0xC0);
  }
  else
  {
    writeData(0x80);
  }
  
  /* Wait for the command to finish */
  waitPoll(RA8875_ELLIPSE, RA8875_ELLIPSE_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level curve drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::curveHelper(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color, bool filled)
{
  /* Set Center Point */
  writeCommand(0xA5);
  writeData(xCenter);
  writeCommand(0xA6);
  writeData(xCenter >> 8);
  writeCommand(0xA7);
  writeData(yCenter); 
  writeCommand(0xA8);
  writeData(yCenter >> 8);

  /* Set Long and Short Axis */
  writeCommand(0xA1);
  writeData(longAxis);
  writeCommand(0xA2);
  writeData(longAxis >> 8);
  writeCommand(0xA3);
  writeData(shortAxis); 
  writeCommand(0xA4);
  writeData(shortAxis >> 8);
  
  /* Set Color */
  writeCommand(0x63);
  writeData((color & 0xf800) >> 11);
  writeCommand(0x64);
  writeData((color & 0x07e0) >> 5);
  writeCommand(0x65);
  writeData((color & 0x001f));

  /* Draw! */
  writeCommand(0xA0);
  if (filled)
  {
    writeData(0xD0 | (curvePart & 0x03));
  }
  else
  {
    writeData(0x90 | (curvePart & 0x03));
  }
  
  /* Wait for the command to finish */
  waitPoll(RA8875_ELLIPSE, RA8875_ELLIPSE_STATUS);
}

/************************* Mid Level ***********************************/

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::GPIOX(bool on) {
  if (on)
    writeReg(RA8875_GPIOX, 1);
  else 
    writeReg(RA8875_GPIOX, 0);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::PWM1out(uint8_t p) {
  writeReg(RA8875_P1DCR, p);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::PWM2out(uint8_t p) {
  writeReg(RA8875_P2DCR, p);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::PWM1config(bool on, uint8_t clock) {
  if (on) {
    writeReg(RA8875_P1CR, RA8875_P1CR_ENABLE | (clock & 0xF));
  } else {
    writeReg(RA8875_P1CR, RA8875_P1CR_DISABLE | (clock & 0xF));
  }
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void Adafruit_RA8875::PWM2config(bool on, uint8_t clock) {
  if (on) {
    writeReg(RA8875_P2CR, RA8875_P2CR_ENABLE | (clock & 0xF));
  } else {
    writeReg(RA8875_P2CR, RA8875_P2CR_DISABLE | (clock & 0xF));
  }
}

/**************************************************************************/
/*!
      Enables or disables the on-chip touch screen controller
*/
/**************************************************************************/
void Adafruit_RA8875::touchEnable(bool on) 
{
  if (on) 
  {
    /* Enable Touch Panel (Reg 0x70) */
    writeReg(RA8875_TPCR0, RA8875_TPCR0_ENABLE        | 
                           RA8875_TPCR0_WAIT_4096CLK  |
                           RA8875_TPCR0_WAKEDISABLE   | 
                           RA8875_TPCR0_ADCCLK_DIV4); // 10mhz max!
    /* Set Auto Mode      (Reg 0x71) */
    writeReg(RA8875_TPCR1, RA8875_TPCR1_AUTO    | 
                           // RA8875_TPCR1_VREFEXT | 
                           RA8875_TPCR1_DEBOUNCE);
    /* Enable TP INT */
    writeReg(RA8875_INTC1, readReg(RA8875_INTC1) | RA8875_INTC1_TP);
  } 
  else
  {
    /* Disable TP INT */
    writeReg(RA8875_INTC1, readReg(RA8875_INTC1) & ~RA8875_INTC1_TP);
    /* Disable Touch Panel (Reg 0x70) */
    writeReg(RA8875_TPCR0, RA8875_TPCR0_DISABLE);
  }
}

/**************************************************************************/
/*!
      Checks if a touch event has occured
      
      @returns  True is a touch event has occured (reading it via
                touchRead() will clear the interrupt in memory)
*/
/**************************************************************************/
bool Adafruit_RA8875::touched(void) 
{
    if (readReg(RA8875_INTC2) & RA8875_INTC2_TP)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**************************************************************************/
/*!
      Reads the last touch event
      
      @args x[out]  Pointer to the uint16_t field to assign the raw X value
      @args y[out]  Pointer to the uint16_t field to assign the raw Y value
      
      @note Calling this function will clear the touch panel interrupt on
            the RA8875, resetting the flag used by the 'touched' function
*/
/**************************************************************************/
bool Adafruit_RA8875::touchRead(uint16_t *x, uint16_t *y) 
{
  uint16_t tx, ty;
  uint8_t temp;
  
  tx = readReg(RA8875_TPXH);
  ty = readReg(RA8875_TPYH);
  temp = readReg(RA8875_TPXYL);
  tx <<= 2;
  ty <<= 2;
  tx |= temp & 0x03;        // get the bottom x bits
  ty |= (temp >> 2) & 0x03; // get the bottom y bits

  *x = tx;
  *y = ty;

  /* Clear TP INT Status */
  writeReg(RA8875_INTC2, RA8875_INTC2_TP);

  return true;
}

/**************************************************************************/
/*!
      Turns the display on or off
*/
/**************************************************************************/
void Adafruit_RA8875::displayOn(bool on) 
{
 if (on) 
   writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPON);
 else
   writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPOFF);
}

/**************************************************************************/
/*!
    Puts the display in sleep mode, or disables sleep mode if enabled
*/
/**************************************************************************/
void Adafruit_RA8875::sleep(bool sleep) 
{
 if (sleep) 
   writeReg(RA8875_PWRR, RA8875_PWRR_DISPOFF | RA8875_PWRR_SLEEP);
 else
   writeReg(RA8875_PWRR, RA8875_PWRR_DISPOFF);
}

/************************* Low Level ***********************************/

/**************************************************************************/
/*!

*/
/**************************************************************************/
void  Adafruit_RA8875::writeReg(uint8_t reg, uint8_t val) 
{
  writeCommand(reg);
  writeData(val);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
uint8_t  Adafruit_RA8875::readReg(uint8_t reg) 
{
  writeCommand(reg);
  return readData();
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void  Adafruit_RA8875::writeData(uint8_t d) 
{
  _cs = 0;
  _spi->write(RA8875_DATAWRITE);
  _spi->write(d);
  _cs = 1;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
uint8_t  Adafruit_RA8875::readData(void) 
{
  _cs = 0;
  _spi->write(RA8875_DATAREAD);
  uint8_t x = _spi->write(0x0);
  _cs = 1;
  return x;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void  Adafruit_RA8875::writeCommand(uint8_t d) 
{
  _cs = 0;
  _spi->write(RA8875_CMDWRITE);
  _spi->write(d);
  _cs = 1;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
uint8_t  Adafruit_RA8875::readStatus(void) 
{
  _cs = 0;
  _spi->write(RA8875_CMDREAD);
  uint8_t x = _spi->write(0x0);
  _cs = 1;
  return x;
}

/**************************************************************************/
/*!
    @brief  Starts the screen calibration process.  Each corner will be
            tested, meaning that each boundary (top, left, right and 
            bottom) will be tested twice and the readings averaged.
*/
/**************************************************************************/
void    Adafruit_RA8875::touchCalibrate(void)
{
  tsPoint_t data;
  
  /* --------------- Welcome Screen --------------- */
  //  Serial.println("Starting the calibration process");
  data = touchRenderCalibrationScreen(_width / 2, _height / 2, 5);
  wait_ms(250);

  /* ----------------- First Dot ------------------ */
  // 10% over and 10% down
  data = touchRenderCalibrationScreen(_width / 10, _height / 10, 5);
  _tsLCDPoints[0].x = _width / 10;
  _tsLCDPoints[0].y = _height / 10;
  _tsTSPoints[0].x = data.x;
  _tsTSPoints[0].y = data.y;
  wait_ms(250);

  /* ---------------- Second Dot ------------------ */
  // 50% over and 90% down
  data = touchRenderCalibrationScreen(_width / 2, _height - _height / 10, 5);
  _tsLCDPoints[1].x = _width / 2;
  _tsLCDPoints[1].y = _height - _height / 10;
  _tsTSPoints[1].x = data.x;
  _tsTSPoints[1].y = data.y;
  wait_ms(250);

  /* ---------------- Third Dot ------------------- */
  // 90% over and 50% down
  data = touchRenderCalibrationScreen(_width - _width / 10, _height / 2, 5);
  _tsLCDPoints[2].x = _width - _width / 10;
  _tsLCDPoints[2].y = _height / 2;
  _tsTSPoints[2].x = data.x;
  _tsTSPoints[2].y = data.y;
  wait_ms(250);

  // Do matrix calculations for calibration and store to EEPROM
  touchSetCalibrationMatrix(&_tsLCDPoints[0], &_tsTSPoints[0], &_tsMatrix);
}
/**************************************************************************/
/*!
    @brief Calculates the difference between the touch screen and the
           actual screen co-ordinates, taking into account misalignment
           and any physical offset of the touch screen.

    @note  This is based on the public domain touch screen calibration code
           written by Carlos E. Vidales (copyright (c) 2001).

           For more information, see the following app notes:

           - AN2173 - Touch Screen Control and Calibration
             Svyatoslav Paliy, Cypress Microsystems
           - Calibration in touch-screen systems
             Wendy Fang and Tony Chang,
             Analog Applications Journal, 3Q 2007 (Texas Instruments)
*/
/**************************************************************************/
int Adafruit_RA8875::touchSetCalibrationMatrix( tsPoint_t * displayPtr, tsPoint_t * screenPtr, tsMatrix_t * matrixPtr)
{
  int  retValue = 0;
  
  matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  
  if( matrixPtr->Divider == 0 )
  {
    retValue = -1 ;
  }
  else
  {
    matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  
    matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                    ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
  
    matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
  
    matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
  
    matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                    ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
  
    matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;

    // Persist data to EEPROM
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_AN, matrixPtr->An);
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_BN, matrixPtr->Bn);
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_CN, matrixPtr->Cn);
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_DN, matrixPtr->Dn);
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_EN, matrixPtr->En);
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_FN, matrixPtr->Fn);
    // eepromWriteS32(CFG_EEPROM_TOUCHSCREEN_CAL_DIVIDER, matrixPtr->Divider);
    // eepromWriteU8(CFG_EEPROM_TOUCHSCREEN_CALIBRATED, 1);
  }

  return( retValue ) ;
} 

/**************************************************************************/
/*!
    @brief  Converts raw touch screen locations (screenPtr) into actual
            pixel locations on the display (displayPtr) using the
            supplied matrix.
            
    @param[out] displayPtr  Pointer to the tsPoint_t object that will hold
                            the compensated pixel location on the display
    @param[in]  screenPtr   Pointer to the tsPoint_t object that contains the
                            raw touch screen co-ordinates (before the
                            calibration calculations are made)
    @param[in]  matrixPtr   Pointer to the calibration matrix coefficients
                            used during the calibration process (calculated
                            via the tsCalibrate() helper function)

    @note  This is based on the public domain touch screen calibration code
           written by Carlos E. Vidales (copyright (c) 2001).
*/
/**************************************************************************/
int Adafruit_RA8875::touchCalibrateTSPoint( tsPoint_t * displayPtr, tsPoint_t * screenPtr, tsMatrix_t * matrixPtr)
{
  int  retValue = 0 ;
  
  if( matrixPtr->Divider != 0 )
  {
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;

    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;
  }
  else
  {
    return -1;
  }

  return( retValue );
}

/**************************************************************************/
/*!
    @brief  Waits for a touch event
*/
/**************************************************************************/
void Adafruit_RA8875::touchWaitForTouchEvent(tsPoint_t * point)
{
  /* Clear the touch data object and placeholder variables */
  memset(point, 0, sizeof(tsPoint_t));
  
  /* Clear any previous interrupts to avoid false buffered reads */
  uint16_t x, y;
  touchRead(&x, &y);
  wait_ms(1);

  /* Wait around for a new touch event (INT pin goes low) */
  while (!touched())
  {
  }
  
  /* Make sure this is really a touch event */
  if (touched())
  {
    touchRead(&x, &y);
    point->x = x;
    point->y = y;
//   Serial.print("Touch: ");
//   Serial.print(point->x); //  //  Serial.print(", "); //  //  Serial.println(point->y);
  }
  else
  {
    point->x = 0;
    point->y = 0;
  }
}

/**************************************************************************/
/*!
    @brief  Renders the calibration screen with an appropriately
            placed test point and waits for a touch event
*/
/**************************************************************************/
tsPoint_t Adafruit_RA8875::touchRenderCalibrationScreen(uint16_t x, uint16_t y, uint16_t radius)
{
  fillScreen(RA8875_WHITE);
  drawCircle(x, y, radius, RA8875_RED);
  drawCircle(x, y, radius + 2, 0x8410);  /* 50% Gray */

  // Wait for a valid touch events
  tsPoint_t point = { 0, 0 };
  
  /* Keep polling until the TS event flag is valid */
  bool valid = false;
  while (!valid)
  {
    touchWaitForTouchEvent(&point);
    if (point.x || point.y) 
    {
      valid = true;
    }
  }
  
  return point;
}

/**************************************************************************/
/*!
      Reads the last touch event
      
      @args x[out]  Pointer to the uint16_t field to assign the calibrated X value
      @args y[out]  Pointer to the uint16_t field to assign the calibrated Y value
      
      @note Calling this function will clear the touch panel interrupt on
            the RA8875, resetting the flag used by the 'touched' function
*/
/**************************************************************************/
bool    Adafruit_RA8875::touchReadCal(uint16_t *tx, uint16_t *ty)
{
    tsPoint_t       tsPoint, tftPoint;
        
    /* Clear any previous interrupts to avoid false buffered reads */
    uint16_t x, y;
    touchRead(&x, &y);
    tsPoint.x = x;
    tsPoint.y = y;
    
    touchCalibrateTSPoint(&tftPoint, &tsPoint, &_tsMatrix);
    
    *tx = tftPoint.x;
    *ty = tftPoint.y;
    
    return true;  
}