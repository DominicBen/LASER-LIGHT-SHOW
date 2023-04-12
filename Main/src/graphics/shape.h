#ifndef SHAPE_H
#define SHAPE_H

#include <Arduino.h>

#include <graphics/graphic.h>
#include <dataobjects/transform.h>
#include <pointer.h>
#include <dataobjects/mat4.h>
class Shape : public Graphic
{
private:
    /* data */
public:
    /// @brief A Enum representing the different possible types for each shape
    /// @example Circle Vs Square

    /// @brief current type of this instance

    // Transform2D transform;
    // Transform2D transform;
    /// @brief Resolution of the shape, The higher this value is, the clearer the shape comes out, but the longer it takes to draw

    Shape();
    Shape(Type type_)
    {
        type = type_;
    }

    void draw(Transform2D transform, Color c) override
    {
        // Serial.println("Print Shape");
        switch (type)
        {
        case Graphic::Circle:
            drawCircle(transform, c);
            break;
        case Graphic::Rectangle:
            drawRect(transform, c);
            break;
        case Graphic::Triangle:
            /* code */
            break;
        case Graphic::Star:
            /* code */
            break;
        case Graphic::Polygon:
            /* code */
            break;
        case Graphic::Diamond:
            /* code */
        case Graphic::AlphaNumeric:
            /* code */
            break;
        default:
            break;
        }
    }
    void drawCircle(Transform2D transform, Color c)
    {
        uint32_t counter;
        bool first = true;
        for (counter = 0; counter < CIRCLE_RESOLUTION * 2; counter++)
        {
            double val = ((2 * PI) / CIRCLE_RESOLUTION) * counter;

            uint16_t xmin = transform.pos.x - transform.scale.x;
            uint16_t xmax = transform.pos.x + transform.scale.x;
            uint16_t ymin = transform.pos.y - transform.scale.y;
            uint16_t ymax = transform.pos.y + transform.scale.y;

            Vec2 new_pos = {map((float)sin(val), -1, 1, xmin, xmax), map((float)cos(val), -1, 1, ymin, ymax)};
            p.pointTo(new_pos);
            if (first)
            {
                p.setColor(c);
                first = false;
            }
        }
        p.setLed(HIGH);
    }
    void drawRect(Transform2D transform, Color c)
    {
        float leftbound = transform.pos.x - transform.scale.x / 2;
        float rightbound = transform.pos.x + transform.scale.x / 2;
        float bottombound = transform.pos.y - transform.scale.y / 2;
        float topbound = transform.pos.y + transform.scale.y / 2;
        // Draw the rectangle
        // Serial.println("Drawing rect");
        // Move Pointer to bottom left position
        Vec2 botleft = Vec2({leftbound, bottombound});
        Vec2 topleft = Vec2({leftbound, topbound});
        Vec2 topright = Vec2({rightbound, topbound});
        Vec2 botright = Vec2({rightbound, bottombound});

        Mat4 points = Mat4({{botleft.x, topleft.x, topright.x, botright.x}, {botleft.y, topleft.y, topright.y, botright.y}, {1, 1, 1, 1}, {1, 1, 1, 1}});
        points = points.rotate(transform.rot, transform.pos);
        // points.print();
        // Vec2 bottleft = Vec2({leftbound, bottombound});
        botleft = Vec2({points(0, 0), points(1, 0)});
        topleft = Vec2({points(0, 1), points(1, 1)});
        topright = Vec2({points(0, 2), points(1, 2)});
        botright = Vec2({points(0, 3), points(1, 3)});
        p.pointTo(botleft);
        p.setColor(c);
        // delayMicroseconds(100);
        p.pointTo(topleft);
        p.pointTo(topright);
        p.pointTo(botright);
        p.pointTo(botleft);

        // Turn off the laser
        p.setLed(HIGH);
    }
    // Shape *setScale(Vec2 scale_) override
    // {
    //     transform.setScale(scale_);
    //     return this;
    // }
    // Shape *setRotation(Vec2 rot_) override
    // {
    //     transform.setRotation(rot_);
    //     return this;
    // }
    // Shape *setPosition(Vec2 pos_) override
    // {
    //     transform.setPosition(pos_);
    //     return this;
    // }

    // Graphic Functions
};

#endif