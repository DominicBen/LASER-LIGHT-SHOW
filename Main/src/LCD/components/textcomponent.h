#pragma once
#include <dataobjects/vec.h>
#include <functional>
#include <LCD/components/component.h>

class TextComponent : public Component
{
private:
    /* data */
public:
    float *data;
    void draw() override;
    // void draw(Vec2 pos_, Vec2 scale_) override;
    bool detectTouch(int x, int y) override { return false; };
    TextComponent *setPos(Vec2 pos_) override
    {
        pos = pos_;
        return this;
    }
    TextComponent *setScale(Vec2 scale_) override
    {
        scale = scale_;
        return this;
    }
    TextComponent(String text_, float *data);
    TextComponent(String text_);

    ~TextComponent(){};
};
