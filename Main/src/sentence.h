#ifndef SENTENCE_H
#define SENTENCE_H

#include <Arduino.h>
#include <vector>
#include <char.h>
#include <string>
class Sentence : public Graphic
{
private:
public:
    /// @brief Vector of symbols to be drawn
    std::vector<Char> word;
    /// @brief This constructor takes in a sentence as a string, and converts it to a sentence object
    /// Any characters that are not supported by the software, are simply ignored
    /// @param word_
    /// @param kerneling_
    /// @param font_size_
    Sentence(std::string word_);
    Sentence(/* args */);
    ~Sentence();
    void draw(Transform2D transform, Color c) override
    {

        p.pointTo({transform.pos.x, transform.pos.y});
        int16_t character_count = word.size();
        int16_t line_count = 0;
        Vec2 newPos = transform.pos - p.format_info.kerneling;

        for (int i = 0; i < character_count; i++)
        {
            if (newPos.x + p.format_info.kerneling + p.format_info.font_size >= WIDTH)
            {
                line_count++;
                newPos = {(float)p.format_info.font_size, newPos.y - p.format_info.font_size * 2};
            }
            else
            {
                newPos = {newPos.x + p.format_info.kerneling, newPos.y};
            }

            Char sym = word[i];
            Transform2D temp = Transform2D().setScale({(float)p.format_info.font_size, (float)p.format_info.font_size}).setPosition(newPos);
            sym.draw(temp, c);
        }
        p.format_info.cursor_pos = {newPos.x + p.format_info.kerneling, newPos.y};
        p.setLed(LOW);
    }
};

#endif // !SENTENCE_H
