#include <screen.h>

void Screen::draw()
{
    Serial.println("drawing all components in the screen");

    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->draw();
    }
}

void Screen::detectTouch()
{
    if ((millis() - menuref->lastTouchInput) < TOUCH_COOLDOWN)
    {

        return;
    }
    uint16_t x;
    uint16_t y;
    tft.touched();

    if (tft.touchRead(&x, &y))
    {
        if (menuref->lastTouchPos.x == x && menuref->lastTouchPos.y == y)
        {
            return;
        }
        Serial.println("touched");
        menuref->lastTouchPos = {x, y};
        menuref->lastTouchInput = millis();
        if (menuref->changedScreens)
        {
            Serial.println("Touch ignored due to just changing screens");
            menuref->changedScreens = false;
            return;
        }

        Serial.print("Touch detected at x=");
        Serial.print(x);
        Serial.print(", y=");
        Serial.println(y);

        x = map(x, 50, 975, 0, LCD_WIDTH);
        y = map(y, 150, 930, 0, LCD_HEIGHT);

        tft.drawCircle(x, y, 15, RA8875_BLUE);
        for (Component *b : components)
        {
            if (b->detectTouch(x, y))
            {
                Serial.println("Touch being detected at base components (prob a list if default)" + b->text);
                return;
            }
        }
    }
}
