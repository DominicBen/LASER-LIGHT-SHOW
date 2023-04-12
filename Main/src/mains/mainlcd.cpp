

#include <LCD/screenwrapper.h>
#include <Adafruit_GFX.h> // Core graphics library
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <LCD/bmp.h>
#include <LCD/menu.h>
#include <LCD/screens/screen.h>

Menu &menu = Menu::getInstance();
Screen *start = new StartScreen();
Screen *gameselect = new GameScreen();
Screen *demos = new DemoScreen();
Screen *settings = new SettingsScreen();
Screen *about = new AboutScreen();
Screen *play = new DemoPlayScreen();

void setup()
{
  Serial.begin(9600);

  if (!SD.begin(sd_cs))
  {
    Serial.println("SDCARD initialization failed!");
    return;
  }
  Serial.println("RA8875 start");
  /* Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_800x480))
  {
    while (1)
      Serial.println("RA8875 Not Found!");
  }
  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);                              // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);

  Serial.print("(");
  Serial.print(tft.width());
  Serial.print(", ");
  Serial.print(tft.height());
  Serial.println(")");

  tft.touchEnable(true);
  tft.graphicsMode(); // go back to graphics mode
  tft.fillScreen(RA8875_BLACK);
  tft.graphicsMode();

  // bmpDraw("caution.bmp", 0, 0);
  // delay(1000);
  // bmpDraw("background.bmp", 0, 0);

  // delay(1000);
  // bmpDraw("background.bmp", 0, 0);

  Serial.println("Adding start screen");

  menu.addScreen(start);      // 0
  menu.addScreen(gameselect); // 1
  menu.addScreen(demos);      // 2
  menu.addScreen(settings);   // 3
  menu.addScreen(about);      // 4
  menu.addScreen(play);       // 5
  Serial.println("Drawing selected screen");
  menu.setSelectedScreen(0);
  Serial.println("in loop");
}

void loop()
{
  menu.getSelectedScreen()->detectTouch();
  menu.updateCurrentDemo();
}
