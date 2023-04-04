#pragma once
#include <vector>
#include <component.h>
#include <button.h>
#include <listcomponent.h>
#include <menu.h>

class Menu;
class Screen
{
private:
    /* data */
public:
    std::vector<Component *> components;

    Menu *menuref;

    void addComponent(Component *b) { components.push_back(b); };

    virtual void draw();
    virtual void detectTouch();
    virtual void init(){};

    Screen(Menu *menu) { menuref = menu; };
    ~Screen() { components.empty(); };
};
