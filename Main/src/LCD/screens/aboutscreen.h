#pragma once
#include <LCD/screens/screen.h>

class AboutScreen : public Screen
{
private:
    /**
     * @brief This is out about page, It provides information about us and our team, thanks a bunch for all your guys have dome
     * means a lot.
     *
     * Dominic
     */
    // Functions
    void draw() override;
    void detectTouch() override;
    void init() override;

public:
    AboutScreen() { init(); };
    ~AboutScreen(){};
};
