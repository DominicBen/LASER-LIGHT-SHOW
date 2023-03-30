#ifndef SHAPE_H
#define SHAPE_H

#include <Arduino.h>

#include <graphic.h>
#include <transform.h>
#include <pointer.h>

class Shape : public Graphic
{
private:
    /* data */
public:
    /// @brief A Enum representing the different possible types for each shape
    /// @example Circle Vs Square
    enum Type
    {
        Circle,
        Square,
        Rectangle,
        Triangle,
        Star,
        Polygon,
        Diamond,
        Grid,
        AlphaNumeric
    };

    /// @brief current type of this instance
    Type type;
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
        case Shape::Circle:
            drawCircle(transform, c);
            break;
        case Shape::Square:
            // Serial.println("Rect draw arm");
            drawRect(transform, c);
            break;
        case Shape::Rectangle:
            drawRect(transform, c);
            break;
        case Shape::Triangle:
            /* code */
            break;
        case Shape::Star:
            /* code */
            break;
        case Shape::Polygon:
            /* code */
            break;
        case Shape::Diamond:
            /* code */
        case Shape::AlphaNumeric:
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
        p.pointTo({leftbound, bottombound});
        p.setColor(c);
        p.pointTo({leftbound, topbound});
        p.pointTo({rightbound, topbound});
        p.pointTo({rightbound, bottombound});
        p.pointTo({leftbound, bottombound});
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