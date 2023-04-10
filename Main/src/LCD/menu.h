#pragma once

#include <Adafruit_GFX.h>
#include <LCD/screenwrapper.h>
#include <vector>
#include <dataobjects/vec.h>
#include <LCD/bmp.h>

// #include <demos/demo.h>
// #include <demos/balls.h>

#include <demos/demo.h>

#define OPTION_WIDTH 350
#define OPTION_HEIGHT 100
#define OPTION_SPACING 50
#define OPTION_Y 50
#define OPTION_X_START 200
class Screen;

class Menu
{
protected:
  Menu() : selectedScreen(0) {}

private:
  std::vector<Screen *> screens;

public:
  u_int16_t selectedScreen = 0;
  u_int16_t previousScreen = 0;
  bool changedScreens = false;
  u_int32_t lastTouchInput = millis();
  Vec2 lastTouchPos = {0, 0};
  Demo *mCurDemo;

  // Singleton Stuff

  Menu(const Menu &) = delete;
  Menu(Menu &&) = delete;
  Menu &operator=(const Menu &) = delete;
  Menu &operator=(Menu &&) = delete;

  static Menu &getInstance()
  {
    static Menu instance;
    return instance;
  }

  void drawSelectedScreen();

  Screen *getSelectedScreen();

  void setSelectedScreen(int option);

  void setCurrentDemo(int demo);
  void setCurrentGame(int game);

  void updateCurrentDemo();

  void nextScreen();

  void prevScreen();

  void addScreen(Screen *s);

  void removeScreen();
};

#include <LCD/screens/screen.h>
