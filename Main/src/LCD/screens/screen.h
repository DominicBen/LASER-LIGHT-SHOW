#pragma once
#include <vector>
#include <LCD/components/component.h>
#include <LCD/menu.h>

class Screen
{
private:
    /* data */
public:
    std::vector<Component *> components;

    Menu &menuref = Menu::getInstance();

    void addComponent(Component *b) { components.push_back(b); };

    virtual void draw();
    virtual void detectTouch();
    virtual void init();

    Screen() { init(); };
    ~Screen() { components.empty(); };
};

#include <LCD/screens/startscreen.h>
#include <LCD/screens/demoscreen.h>
#include <LCD/screens/gamescreen.h>
#include <LCD/screens/settingsscreen.h>
#include <LCD/screens/demoplayscreen.h>
#include <LCD/screens/aboutscreen.h>