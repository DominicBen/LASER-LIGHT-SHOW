#include <sentence.h>
Sentence::Sentence(/* args */)
{
}
Sentence::Sentence(std::string word_)
{
    for (size_t i = 0; i < word_.size(); i++)
    {
        Mesh m = Mesh(word_[i]);
        if (m.valid)
        {
            word.push_back(Char(m));
        }
    }
}

Sentence::~Sentence()
{
}
