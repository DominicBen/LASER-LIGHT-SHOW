#pragma once
#include <LCD/screens/screen.h>

class GameScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;
    int mCurrentGame = 0;
    int mNumGames = 4;
    Vec2 mGameIconSize = {200, 189};

public:
    GameScreen() { init(); };
    ~GameScreen(){};
};