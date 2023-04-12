#pragma once
#include <vector>
#include <LCD/components/component.h>
class ListComponent : public Component
{
private:
    /* data */
public:
    std::vector<Component *> components;

    // const int COMPONENT_Y_START = 0;
    // const int COMPONENT_X_START = LCD_WIDTH / 2;
    const int COMPONENT_SPACING = 40;
    // const int COMPONENT_X_SCALE = 300;

    void draw() override;
    // void draw(Vec2 pos_, Vec2 scale_) override;
    bool detectTouch(int x, int y) override;
    ListComponent *addComponent(Component *component)
    {
        components.push_back(component);
        return this;
    }
    ListComponent(/* args */){};
    ListComponent(String text_) : Component(text_) {}
    ListComponent(Vec2 pos_, Vec2 scale_) : Component(pos_, scale_){};

    ~ListComponent();
};
