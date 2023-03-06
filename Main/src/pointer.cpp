#include <pointer.h>

Pointer::Pointer()
{

    current_pos = {0, 0};
    pinMode(LED_PIN, OUTPUT);
    // Set pointer at center of screen
    dac.init();
    dac.write(0, HEIGHT / 2);
    dac.write(1, WIDTH / 2);
}

void Pointer::drawShape(Shape s)
{
    switch (s.type)
    {
    case Shape::Circle:
        drawCircle(s);
        break;
    case Shape::Square:
        drawRect(s);
        break;
    case Shape::Rectangle:
        drawRect(s);
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

void Pointer::moveTowards(Vec2 pos)
{
    int16_t xstep = (current_pos.x - pos.x) >= 0 ? 1 : -1;
    int16_t ystep = (current_pos.y - pos.y) >= 0 ? 1 : -1;
    Vec2 newPos = pos;

    while (current_pos.x != newPos.x || current_pos.y != newPos.y)
    {
        if (current_pos.x != newPos.x)
        {
            newPos.x += xstep;
        }
        if (current_pos.y != newPos.y)
        {
            newPos.x += ystep;
        }
        pointTo(newPos);
    }
}

void Pointer::pointTo(Vec2 pos)
{
    // Handles variable lag depending on what distance the laser pointer needs to travel.
    Vec2 distance = current_pos - pos;
    distance.absVec();
    float distance_traveled = max(distance.x, distance.y);
    float slope = (DELAY_RATE - CONSTANT_LAG) / (float)(4095 - 0);
    u_int32_t total_delay = (u_int32_t)(slope * (distance_traveled)) + CONSTANT_LAG;
    // Clamp value to the window
    Vec2 newPos = pos.clamp(0, WIDTH);

    if (current_pos.x != newPos.x)
    {
        dac.write(0, newPos.x);
        current_pos.x = newPos.x;
    }
    if (current_pos.y != newPos.y)
    {
        dac.write(1, newPos.y);
        current_pos.y = newPos.y;
    }

    dac.drive();
    delayMicroseconds(total_delay);
}
void Pointer::toggleLed()
{
    digitalToggle(LED_PIN);
}
void Pointer::toggleLed(int8_t state)
{
    digitalWrite(LED_PIN, state);
}
void Pointer::drawCircle(int x, int y, int r)
{
    Shape circle = Shape(Shape::Circle, Transform2D().setPosition({x, y}).setScale({r, r}));
    drawCircle(circle);
}
void Pointer::drawCircle(Shape s)
{
    uint32_t counter;
    bool first = true;
    for (counter = 0; counter < CIRCLE_RESOLUTION * 2; counter++)
    {
        double val = ((2 * PI) / CIRCLE_RESOLUTION) * counter;

        uint16_t xmin = s.transform.pos.x - s.transform.scale.x;
        uint16_t xmax = s.transform.pos.x + s.transform.scale.x;
        uint16_t ymin = s.transform.pos.y - s.transform.scale.y;
        uint16_t ymax = s.transform.pos.y + s.transform.scale.y;

        Vec2 new_pos = {map((float)sin(val), -1, 1, xmin, xmax), map((float)cos(val), -1, 1, ymin, ymax)};
        pointTo(new_pos);
        if (first)
        {
            toggleLed(HIGH);
            first = false;
        }
    }
    toggleLed(LOW);
}

void Pointer::drawRect(int x, int y, int w, int h)
{
    Shape s = Shape(Shape::Rectangle, Transform2D().setPosition({x, y}).setScale({w / 2, h / 2}));
    drawRect(s);
}

void Pointer::drawRect(Shape s)
{
    float leftbound = s.transform.pos.x - s.transform.scale.x / 2;
    float rightbound = s.transform.pos.x + s.transform.scale.x / 2;
    float bottombound = s.transform.pos.y - s.transform.scale.y / 2;
    float topbound = s.transform.pos.y + s.transform.scale.y / 2;
    // Draw the rectangle

    // Move Pointer to bottom left position
    pointTo({leftbound, bottombound});
    toggleLed(HIGH);
    pointTo({leftbound, topbound});
    pointTo({rightbound, topbound});
    pointTo({rightbound, bottombound});
    pointTo({leftbound, bottombound});
    // Turn off the laser
    toggleLed(LOW);
}

void Pointer::drawGrid(Grid g)
{
    for (int16_t i = -g.cols / 2; i <= g.cols / 2; i++)
    {
        for (int16_t j = -g.rows / 2; j <= g.rows / 2; j++)
        {
            float newx = (WIDTH / 2) + (g.s.transform.scale.x * 2 * i);
            float newy = (HEIGHT / 2) + (g.s.transform.scale.y * 2 * j);
            g.s.transform.pos = {newx, newy};
            drawShape(g.s);
        }
    }
}

// void Pointer::draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols)
// {
//     struct Point3D vertex[8] = {{-1, 1, -1}, {1, 1, -1}, {-1, -1, -1}, {1, -1, -1}, {-1, 1, 1}, {1, 1, 1}, {-1, -1, 1}, {1, -1, 1}};
// }

// void Pointer::draw_mesh(Mesh m)
// {
//     Vec2 newpos;
//     // delay(1000);
//     for (u_int16_t i = 0; i < m.travel_order.size(); i++)
//     {
//         newpos = Vec2::mapVec(m.verticies[m.travel_order[i]], -1, 1, 0, 1000);
//         newpos.x += WIDTH / 2;
//         newpos.y += HEIGHT / 2;
//         point_to({newpos.x, newpos.y});

//         delayMicroseconds(400);

//         if (!m.led_info[i])
//         {
//             delayMicroseconds(400);
//         }
//         toggle_led(m.led_info[i]);
//     }
// }
void Pointer::drawChar(int x, int y, char c, int size)
{
    Char character = Char(c);
    character.transform.setPosition({x, y}).setScale({size, size});
    drawChar(character);
}
void Pointer::drawChar(Char c)
{
    Vec2 newpos;

    for (u_int16_t i = 0; i < c.m.travel_order.size(); i++)
    {
        // Increases size of vertices
        newpos.y = map(c.m.verticies[c.m.travel_order[i]].y, -1, 1, 0, c.transform.scale.y) + c.transform.pos.y;
        newpos.x = map(c.m.verticies[c.m.travel_order[i]].x, -1, 1, 0, c.transform.scale.x) + c.transform.pos.x;
        pointTo({newpos.x, newpos.y});
        toggleLed(c.m.led_info[i]);
    }
    toggleLed(LOW);
}
void Pointer::print(Sentence sentence)
{
    pointTo({sentence.transform.pos.x, sentence.transform.pos.y});
    int16_t character_count = sentence.word.size();
    int16_t line_count = 0;
    Vec2 newPos = sentence.transform.pos - format_info.kerneling;

    for (int i = 0; i < character_count; i++)
    {
        if (newPos.x + format_info.kerneling + format_info.font_size >= WIDTH)
        {
            line_count++;
            newPos = {format_info.font_size, newPos.y - format_info.font_size * 2};
        }
        else
        {
            newPos = {newPos.x + format_info.kerneling, newPos.y};
        }

        Char sym = sentence.word[i];
        sym.transform = Transform2D().setScale({(float)format_info.font_size, (float)format_info.font_size}).setPosition(newPos);
        drawChar(sym);
    }
    format_info.cursor_pos = {newPos.x + format_info.kerneling, newPos.y};
    toggleLed(LOW);
}
void Pointer::print(std::string sen)
{
    Sentence sentence = Sentence(sen);
    sentence.transform.setPosition(format_info.cursor_pos);
    print(sentence);
}
void Pointer::println(std::string sen)
{
    Sentence sentence = Sentence(sen);
    sentence.transform.setPosition({format_info.font_size, format_info.cursor_pos.y - format_info.font_size * 2});
    print(sentence);
}

void Pointer::drawILDA(ILDA &ild)
{
    Serial.print("drawing ILDA with frames");
    Serial.println(ild.num_frames);

    for (u_int16_t i = 0; i < ild.num_frames; i++)
    {

        Serial.print("drawing frame ");
        Serial.print(i);
        Serial.print(" with points ");
        Serial.println(ild.frames[i].number_points);
        for (u_int16_t j = 0; j < ild.frames[i].number_points; j++)
        {
            Vec2 point = Vec2(ild.frames[i].points[j].x, ild.frames[i].points[j].y);

            point.mapVec(-32768, 32767, (WIDTH / 2 - 2000), (WIDTH / 2 + 2000));
            // toggles led's based on status code
            if ((ild.frames[i].points[j].status_code & 0b01000000) == 0)
            {
                toggleLed(HIGH);
            }
            else
            {
                toggleLed(LOW);
            }
            pointTo(point);
        }

        delay(20);
    }
}
