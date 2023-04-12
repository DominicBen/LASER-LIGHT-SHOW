#pragma once

#include <LCD/screens/screen.h>

class DemoScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;

public:
    DemoScreen() { init(); };
    ~DemoScreen(){};
};
