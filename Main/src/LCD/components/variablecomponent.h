#pragma once
#include <vector>
#include <LCD/components/component.h>

class VariableComponent : public Component
{
private:
    std::vector<Component *> components;
    /* data */
public:
    float incrementer = 1;
    float large_incrementer = 2;
    float *variable;
    using Callback = std::function<void(int x)>;

    void draw() override;
    // void draw(Vec2 pos_, Vec2 scale_) override;
    bool detectTouch(int x, int y) override;
    // VariableComponent *addComponent(Component *button)
    // {
    //     components.push_back(button);
    //     return this;
    // }
    VariableComponent *setPos(Vec2 pos_) override
    {
        pos = pos_;
        return this;
    }
    VariableComponent *setScale(Vec2 scale_) override
    {
        scale = scale_;
        return this;
    }
    // VariableComponent(/* args */){};
    VariableComponent(Vec2 pos_, Vec2 scale_, String text, float incrementer_, float large_incrementer_, float *variable, Callback callback);

    ~VariableComponent();
};
