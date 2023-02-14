#ifndef SENTENCE_H
#define SENTENCE_H

#include <Arduino.h>
#include <vector>
#include <symbol.h>
#include <string>
class Sentence
{
private:
public:
    int16_t kernaling = 500;
    int16_t font_size = 500;
    Transform t;
    std::vector<Symbol> word;
    Sentence(std::string word_, int16_t kernaling_, int16_t font_size_);
    Sentence(/* args */);
    ~Sentence();
};

Sentence::Sentence(/* args */)
{
}
Sentence::Sentence(std::string word_, int16_t kernaling_, int16_t font_size_)
{
    kernaling = kernaling_;
    font_size = font_size_;
    for (size_t i = 0; i < word_.size(); i++)
    {
        Mesh m = Mesh(word_[i]);
        if (m.valid)
        {
            word.push_back(Symbol(m));
        }
    }
}

Sentence::~Sentence()
{
}

#endif // !SENTENCE_H
