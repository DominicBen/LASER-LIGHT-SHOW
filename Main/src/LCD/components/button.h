#pragma once
#include <dataobjects/vec.h>
// #include <functional>
#include <LCD/components/component.h>

class Button : public Component
{
private:
    /* data */
public:
    using Callback = std::function<void(int x)>;
    /// @brief Callback function that is call when the button is pressed
    Callback mCallback;
    /// @brief  Callback variable for additional functionality
    int mCallbackValue = 0;

    void draw() override;
    // void draw(Vec2 pos_, Vec2 scale_) override;
    bool detectTouch(int x, int y) override;

    void drawtest();

    Button *setPos(Vec2 pos_) override
    {
        pos = pos_;
        return this;
    }
    Button *setScale(Vec2 scale_) override
    {
        scale = scale_;
        return this;
    }
    Button(String text_, Callback callback, int callback_value_);
    ~Button();
};
