#pragma once
#include <vector>
#include <component.h>
#include <button.h>
class ListComponent : public Component
{
private:
    /* data */
public:
    std::vector<Button *> buttons;

    const int BUTTON_Y_START = 50;
    const int BUTTON_X_START = LCD_WIDTH / 2;
    const int BUTTON_SPACING = 40;
    const int BUTTON_X_SCALE = 300;

    void draw() override;
    void draw(Vec2 pos_, Vec2 scale_) override;
    bool detectTouch(int x, int y) override;
    ListComponent *addButton(Button *button)
    {
        buttons.push_back(button);
        return this;
    }
    ListComponent(/* args */){};
    ListComponent(std::vector<String> buttonTexts);
    ListComponent(Vec2 pos_, Vec2 scale_) : Component(pos_, scale_){};

    ~ListComponent();
};
