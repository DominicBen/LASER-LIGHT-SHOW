/**
 * @file Pointer.h
 * @author Laser Light Show
 * @brief Pointer is a singleton class incharge of moving where the laser projects on a screen
 * It has sole access to the movement of the xdim / ydim galvos, aswell as toggling the state of the led
 * Along with this control, Pointer has several helper fuctions for drawing basic shapes and objects
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef POINTER_H
#define POINTER_H

#include <Arduino.h>
#include <constants.h>
#include <MCP4922.h>

#include <vec.h>
#include <color.h>

// #include <shape.h>
// #include <mesh.h>
// #include <char.h>
// #include <sentence.h>
// #include <ILDA.h>

#include <string>

/**
 * @brief
 * This class is responsible for controlling the galvo motors and led.
 * The class is a "singleton" meaning there can only be one instance of this class at a time
 * This allows the class to be called for anywhere in the code
 *
 */

struct Cursor_info
{
    int16_t font_size = FONT_SIZE;
    int16_t kerneling = KERNELING;

    // u_int16_t lines = 0;
    Vec2 cursor_pos;
};

class Pointer
{
private:
protected:
    Pointer();

public:
    /// @brief Current position of the galvo, updated on point_to()
    Vec2 current_pos;
    /// @brief Current cursor data of the cursor, used for where to print words
    Cursor_info format_info;
    /// @brief Current color of the laser
    Color cur_color;
    /// @brief Dac object used to control the galvo DACS
    MCP4922 dac = MCP4922(CS, LDAC);

    void init()
    {
        pinMode(RED_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
        pinMode(BLUE_LED, OUTPUT);
        setLed(LOW);
        format_info.kerneling = KERNELING;
        format_info.font_size = FONT_SIZE;
    }
    /**
     * @brief Points the laser to the provided position, pos
     * 0,0 is the bottom left of the screen
     * 4095,4095 is the top left of the screen
     * WIDTH/2, HEIGHT/2 is the middle of the screen
     *
     * @param pos
     */
    void pointTo(Vec2 pos);

    /**
     * @brief Moves the pointer towards the provided pos at a given speed, helpful if you want
     * longer and exaggerated lines
     * @param pos
     */
    void moveTowards(Vec2 pos);
    /**
     * @brief toggle_led toggles the current state of the led
     */
    // void toggleRed();
    // void toggleBlue();
    // void toggleGreen();

    void setRed(int8_t state);
    void setBlue(int8_t state);
    void setGreen(int8_t state);

    // void toggleLed();
    void setColor(Color c);
    void setLed(int8_t state);
    // Singleton Constructors
    // only be one
    // These constructors call an error when attempting to copy a pointer instance, as there can
    Pointer(const Pointer &) = delete;
    Pointer(Pointer &&) = delete;
    Pointer &operator=(const Pointer &) = delete;
    Pointer &operator=(Pointer &&) = delete;

    // void println(std::string sen);
    // void print(std::string sen);

    // // user friendly function calls
    // /**
    //  * @brief draws a rectangle centered at x, y with the width and height
    //  *
    //  * @param x
    //  * @param y
    //  * @param w
    //  * @param h
    //  */
    // void drawRect(int x, int y, int w, int h);
    // void drawCircle(int x, int y, int r);
    // void drawChar(int x, int y, char c, int size);

    // void drawILDA(ILDA &ild);

    static Pointer &getInstance()
    {
        static Pointer instance;
        return instance;
    }
};

#endif