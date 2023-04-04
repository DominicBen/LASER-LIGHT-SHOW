#pragma once
#include <vec.h>
#include <functional>
#include <component.h>

class Button : public Component
{
private:
    /* data */
public:
    using Callback = std::function<void()>;
    /// @brief Callback function that is call when the button is pressed
    Callback m_callback;

    void draw() override;
    void draw(Vec2 pos_, Vec2 scale_) override;
    bool detectTouch(int x, int y) override;

    Button(String text_, Callback callback);
    ~Button();
};
