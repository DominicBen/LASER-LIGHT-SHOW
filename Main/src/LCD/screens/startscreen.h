#pragma once
#include <LCD/screens/screen.h>

class StartScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;

public:
    StartScreen() { init(); };
    ~StartScreen(){};
};