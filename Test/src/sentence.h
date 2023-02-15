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
    /// @brief The distance between symbols
    int16_t kerneling = 500;
    /// @brief The size of each symbol, where 4095 is the whole screen
    int16_t font_size = 500;
    /// @brief The transform of the sentence, where the origin is bottom left of the first letter
    Transform2D t;
    /// @brief Vector of symbols to be drawn
    std::vector<Symbol> word;
    /// @brief This constructor takes in a sentence as a string, and converts it to a sentence object
    /// Any characters that are not supported by the software, are simply ignored
    /// @param word_
    /// @param kerneling_
    /// @param font_size_
    Sentence(std::string word_, int16_t kerneling_, int16_t font_size_);
    Sentence(/* args */);
    ~Sentence();
};

#endif // !SENTENCE_H
