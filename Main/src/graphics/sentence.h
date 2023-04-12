#ifndef SENTENCE_H
#define SENTENCE_H

#include <Arduino.h>
#include <vector>
#include <graphics/graphic.h>
#include <string>
class Char;
class Sentence : public Graphic
{
private:
public:
    /// @brief Vector of symbols to be drawn
    std::vector<Char> mWord;
    u_int64_t mDrawCount = 0;
    /// @brief This constructor takes in a sentence as a string, and converts it to a sentence object
    /// Any characters that are not supported by the software, are simply ignored
    void
    draw(Transform2D transform, Color c, float kerneling, float font_size);
    void draw(Transform2D transform, Color c) override;

    Sentence(std::string word_);
    Sentence(/* args */);
    ~Sentence();
};

#endif // !SENTENCE_H
