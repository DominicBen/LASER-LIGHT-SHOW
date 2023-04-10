#include <LCD/menu.h>

void Menu::drawSelectedScreen()
{
    Serial.println("drawing currently selected screen ... " + selectedScreen);
    // bmpDraw("background.bmp", 0, 0);
    if (selectedScreen >= screens.size())
        screens[0]->draw();
    screens[selectedScreen]->draw();
}

Screen *Menu::getSelectedScreen()
{
    return screens[selectedScreen];
}

void Menu::setSelectedScreen(int option)
{
    previousScreen = selectedScreen;
    selectedScreen = option;
    drawSelectedScreen();
}

void Menu::setCurrentDemo(int demo)
{
    free(mCurDemo);
    switch (demo)
    {
    case 0:
    {
        // Demo *temp = new ShapesDemo();
        // temp->init();
        // mCurDemo = temp;
    }
    case 1:
    {
        Demo *temp = new GridDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 2:
    {
        Demo *temp = new CharactersDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 3:
    {
        Demo *temp = new SentencesDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 4:
    {
        Demo *temp = new VelocityDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 5:
    {
        Demo *temp = new GravityDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 6:
    {
        Demo *temp = new CollisionDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 7:
    {
        Demo *temp = new BallDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 8:
    {
        Demo *temp = new BeeMovieDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 9:
    {
        Demo *temp = new ILDADemo();
        temp->init();
        mCurDemo = temp;
        break;
    }
    case 10:
    {
        Demo *temp = new BadAppleDemo();
        temp->init();
        mCurDemo = temp;
        break;
    }

    break;

    default:
        break;
    }
}

void Menu::setCurrentGame(int game)
{
    free(mCurDemo);
    switch (game)
    {
    case 0:
    {
        Demo *temp = new Pong();
        temp->init();
        mCurDemo = temp;
        break;
    }

    default:
        break;
    }
}

void Menu::updateCurrentDemo()
{
    if (mCurDemo)
    {
        mCurDemo->draw();
        mCurDemo->update();
    }
}

void Menu::nextScreen()
{
    previousScreen = selectedScreen;
    selectedScreen++;
    if (selectedScreen >= screens.size())
    {
        selectedScreen = 0;
    }
    drawSelectedScreen();
}

void Menu::prevScreen()
{
    u_int16_t temp = previousScreen;
    previousScreen = selectedScreen;
    selectedScreen = temp;

    drawSelectedScreen();
}

void Menu::addScreen(Screen *s)
{
    Serial.println("Menu:: Adding screen with buttons " + s->components.size());
    screens.push_back(s);
}
void Menu::removeScreen()
{
}