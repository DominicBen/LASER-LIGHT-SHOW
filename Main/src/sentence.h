#ifndef SENTENCE_H
#define SENTENCE_H

#include <Arduino.h>
#include <vector>
#include <char.h>
#include <string>
class Sentence
{
private:
public:
    /// @brief The transform of the sentence, where the origin is bottom left of the first letter
    Transform2D transform;
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
};

#endif // !SENTENCE_H
