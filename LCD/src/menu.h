#pragma once

#include <Adafruit_GFX.h>
#include <screenwrapper.h>
#include <vector>
#include <vec.h>
#include <screen.h>
#include <bmp.h>

#define OPTION_WIDTH 350
#define OPTION_HEIGHT 100
#define OPTION_SPACING 50
#define OPTION_Y 50
#define OPTION_X_START 200

class Screen;
class Menu
{
private:
  std::vector<Screen *> screens;

public:
  int selectedScreen = 0;
  int previousScreen = 0;
  bool changedScreens = false;
  int lastTouchInput = millis();
  Vec2 lastTouchPos = {0, 0};
  Menu() : selectedScreen(0) {}

  void drawSelectedScreen();

  Screen *getSelectedScreen();

  void setSelectedScreen(int option);

  void nextScreen();

  void prevScreen();

  void addScreen(Screen *s);

  void removeScreen();
};
