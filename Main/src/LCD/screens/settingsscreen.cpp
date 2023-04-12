#include <LCD/screens/settingsscreen.h>
void SettingsScreen::init()
{
    Serial.println("SettingsScreen::defining main screen");
    Screen::init();

    auto backCallback = [&](int x) -> void
    {
        menuref.prevScreen();
    };
    auto changeVolume = [&](int x) -> void
    {
        cur_volume += x;
        if (cur_volume < 0)
            cur_volume = 0;
        if (cur_volume > 100)
            cur_volume = 100;

        Serial.println(cur_volume);
        draw();
    };
    auto changeA = [&](int x) -> void
    {
        a += x;
        if (a < 0)
            a = 0;
        if (a > 100)
            a = 100;

        Serial.println(a);
        draw();
    };
    auto changeB = [&](int x) -> void
    {
        b += x;
        if (b < 0)
            b = 0;
        if (b > 100)
            b = 100;

        Serial.println(b);
        draw();
    };
    // Vec2 varpos = {(int)(LCD_WIDTH * (1 / 6)), (int)(LCD_HEIGHT * (3 / 4))};
    Vec2 varscale = {(int)(LCD_WIDTH / 6), (int)(LCD_HEIGHT / 2)};
    // Vec2 varpos = {LCD_WIDTH / 2, LCD_HEIGHT / 2};
    // Vec2 varscale = {LCD_WIDTH / 2, 300};

    components.push_back((new VariableComponent({LCD_WIDTH * 1 / 6, LCD_HEIGHT / 4}, varscale, "Volume", 5, 10, &cur_volume, changeVolume)));
    components.push_back((new VariableComponent({LCD_WIDTH * 3 / 6, LCD_HEIGHT / 4}, varscale, "A", 5, 10, &a, changeA)));
    components.push_back((new VariableComponent({LCD_WIDTH * 5 / 6, LCD_HEIGHT / 4}, varscale, "B", 5, 10, &b, changeB)));

    // components.push_back((new VariableComponent({(int)LCD_HEIGHT * (3 / 4), (int)LCD_WIDTH * (1 / 6)}, {(int)LCD_HEIGHT / 2, (int)LCD_WIDTH / 3}, "Volume", 5, 10, cur_volume, changeVolume)));
    // components.push_back((new VariableComponent({(int)LCD_HEIGHT * (3 / 4), (int)LCD_WIDTH * (1 / 6)}, {(int)LCD_HEIGHT / 2, (int)LCD_WIDTH / 3}, "Volume", 5, 10, cur_volume, changeVolume)));

    components.push_back((new Button("Back", backCallback, 0))->setScale({150, 100})->setPos({100, LCD_HEIGHT - 100}));
    // Component *volumeUp = (new Button("Up", changeVolume, 1))->setScale({150, 50})->setPos({100, LCD_HEIGHT - 250});
    // Component *volumeText = (new TextComponent("Volume", cur_volume))->setScale({150, 150})->setPos({100, LCD_HEIGHT - 175});
    // Component *volumeDown = (new Button("Down", changeVolume, -1))->setScale({150, 50})->setPos({100, LCD_HEIGHT - 150});

    // // Component *back = (new Button("Back", back, 0))->setScale({50, 50})->setPos({100, 100});

    // components.push_back(backButton);
    // components.push_back(volumeUp);
    // components.push_back(volumeDown);
    // components.push_back(volumeText);
}

void SettingsScreen::draw()
{

    Screen::draw();
}

void SettingsScreen::detectTouch()
{
    Screen::detectTouch();
}