#include <graphics/sentence.h>
Sentence::Sentence(/* args */)
{
}
Sentence::~Sentence()
{
}
Sentence::Sentence(std::string word_)
{
    for (size_t i = 0; i < word_.size(); i++)
    {
        Mesh m = Mesh(word_[i]);
        if (m.valid)
        {
            mWord.push_back(Char(m));
        }
    }
}

void Sentence::draw(Transform2D transform, Color c)
{

    p.pointTo({transform.pos.x, transform.pos.y});
    int16_t character_count = mWord.size();
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

        Char sym = mWord[i];
        Transform2D temp = Transform2D().setScale({(float)p.format_info.font_size, (float)p.format_info.font_size}).setPosition(newPos);
        if (c == RAINBOW)
        {
            sym.draw(temp, (Color)((i + mDrawCount) % 6));
            mDrawCount++;
        }
        else
            sym.draw(temp, c);
    }
    p.format_info.cursor_pos = {newPos.x + p.format_info.kerneling, newPos.y};
    p.setLed(HIGH);
}
void Sentence::draw(Transform2D transform, Color c, float kerneling, float font_size)
{

    p.pointTo({transform.pos.x, transform.pos.y});
    int16_t character_count = mWord.size();
    int16_t line_count = 0;
    Vec2 newPos = transform.pos - kerneling;

    for (int i = 0; i < character_count; i++)
    {
        if (newPos.x + kerneling + font_size >= WIDTH)
        {
            line_count++;
            newPos = {(float)font_size, newPos.y - font_size * 2};
        }
        else
        {
            newPos = {newPos.x + kerneling, newPos.y};
        }

        Char sym = mWord[i];
        Transform2D temp = Transform2D().setScale({(float)font_size, (float)font_size}).setPosition(newPos);
        sym.draw(temp, c);
    }
    p.format_info.cursor_pos = {newPos.x + p.format_info.kerneling, newPos.y};
    p.setLed(LOW);
}