#pragma once

#include <LCD/screens/screen.h>

class DemoPlayScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;
    float mGameSpeed = 1;
    float mA = 1;
    bool mIsPaused = false;

public:
    DemoPlayScreen() { init(); };
    ~DemoPlayScreen(){};
};
