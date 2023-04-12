#pragma once
#include <LCD/screens/screen.h>
class SettingsScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;

    Vec2 game_icon_size = {200, 189};

public:
    float cur_volume = 50;
    float a = 50;
    float b = 50;
    SettingsScreen() { init(); };
    ~SettingsScreen(){};
};
