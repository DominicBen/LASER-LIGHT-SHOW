#include <LCD/screens/gamescreen.h>

void GameScreen::init()
{
    Serial.println("GameScreen::defining main screen");
    Screen::init();

    auto backCallback = [&](int x) -> void
    {
        menuref.setSelectedScreen(0);
    };
    auto loadGame = [&](int x) -> void
    {
        menuref.setSelectedScreen(5);
    };
    auto nextGame = [&](int x) -> void
    {
        mCurrentGame++;
        if (mCurrentGame >= mNumGames)
            mCurrentGame = 0;
        draw();
    };
    auto lastGame = [&](int x) -> void
    {
        mCurrentGame--;
        if (mCurrentGame < 0)
            mCurrentGame = mNumGames - 1;
        draw();
    };
    Component *backButton = (new Button("Menu", backCallback, 0))->setScale({150, 100})->setPos({100, 100});
    Component *nextButton = (new Button("<", lastGame, 0))->setScale({150, 100})->setPos({100, LCD_HEIGHT - 100});
    Component *prevButton = (new Button(">", nextGame, 0))->setScale({150, 100})->setPos({LCD_WIDTH - 100, LCD_HEIGHT - 100});

    // Component *back = (new Button("Back", back, 0))->setScale({50, 50})->setPos({100, 100});

    components.push_back(backButton);
    components.push_back(nextButton);
    components.push_back(prevButton);
    components.push_back((new Button("", loadGame, mCurrentGame))
                             ->setPos(MIDDLE)
                             ->setScale(mGameIconSize));
}

void GameScreen::draw()
{
    Screen::draw();
    switch (mCurrentGame)
    {
    case 0:
        bmpDraw("pong.bmp", LCD_WIDTH / 2 - mGameIconSize.x / 2, LCD_HEIGHT / 2 - mGameIconSize.y / 2);
        break;
    case 1:
        bmpDraw("flappy_bird.bmp", LCD_WIDTH / 2 - mGameIconSize.x / 2, LCD_HEIGHT / 2 - mGameIconSize.y / 2);
        break;
    case 2:
        bmpDraw("tetris.bmp", LCD_WIDTH / 2 - mGameIconSize.x / 2, LCD_HEIGHT / 2 - mGameIconSize.y / 2);
        break;
    case 3:
        bmpDraw("astroids.bmp", LCD_WIDTH / 2 - mGameIconSize.x / 2, LCD_HEIGHT / 2 - mGameIconSize.y / 2);
        break;

    default:
        break;
    }
}

void GameScreen::detectTouch()
{
    Screen::detectTouch();
}