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
    // CS 10,
    // LDAC 9
    // MOSI 11
    // SCK 13

protected:
    Pointer();

public:
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
    void toggleRed();
    void toggleBlue();
    void toggleGreen();

    void setRed(int8_t state);
    void setBlue(int8_t state);
    void setGreen(int8_t state);

    void toggleLed();
    void setLed(int8_t state);
    // Singleton Constructors
    // only be one
    // These constructors call an error when attempting to copy a pointer instance, as there can
    Pointer(const Pointer &) = delete;
    Pointer(Pointer &&) = delete;
    Pointer &operator=(const Pointer &) = delete;
    Pointer &operator=(Pointer &&) = delete;

    /// @brief Current position of the galvo, updated on point_to()
    Vec2 current_pos;
    /// @brief Current cursor data of the cursor, used for where to print words
    Cursor_info format_info;

    MCP4922 dac = MCP4922(CS, LDAC);

    // /**
    //  * @brief Draws a given shape s, the algorithm used depends on the shape's type
    //  * @param s
    //  */
    // // // void draw_shape(Shape s);
    // void drawCircle(Shape c);
    // void drawRect(Shape s);
    // /// @brief Draws a grid of shapes g, default 3x3
    // /// @param g
    // void drawGrid(Grid g);
    // /// @brief Draws a symbol object s, if first_word is true, a small delay is added before the laser beings drawing
    // /// @param s
    // /// @param first_word
    // void drawChar(Char s);
    // void drawShape(Shape s);

    // // /// @brief Draws a mesh object, these are objects that contain a specific set of vertices to be draw.
    // // /// This includes characters
    // // /// @param m
    // // void drawMesh(Mesh m);
    // void println(std::string sen);
    // void print(std::string sen);
    // /// @brief Prints a string at the current location
    // /// @param sen
    // void print(Sentence sen);
    // // WIP
    // void draw3DCube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols);
    // /// @brief returns a reference to the singleton instance of this class
    // /// @return

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