#include <sentence.h>
Sentence::Sentence(/* args */)
{
}
Sentence::Sentence(std::string word_, int16_t kernaling_, int16_t font_size_)
{
    kerneling = kernaling_;
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
