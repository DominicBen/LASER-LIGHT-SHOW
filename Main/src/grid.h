#pragma once
#include <Arduino.h>
#include <graphic.h>

class Grid : public Graphic
{
public:
    /// @brief The rows of shape s to be drawn
    int16_t rows = 3;
    /// @brief the cols of shape s to be drawn
    int16_t cols = 3;
    /// @brief The shape that is to be displayed in a grid fashion.
    Graphic *s;
    Grid(Graphic *s_) { s = s_; }
    Grid() {}

    void draw()
    {
        for (int16_t i = -cols / 2; i <= cols / 2; i++)
        {
            for (int16_t j = -rows / 2; j <= rows / 2; j++)
            {
                float newx = (WIDTH / 2) + (transform.scale.x * 2 * i);
                float newy = (HEIGHT / 2) + (transform.scale.y * 2 * j);
                s->transform.pos = {newx, newy};
                s->draw();
            }
        }
    }
};