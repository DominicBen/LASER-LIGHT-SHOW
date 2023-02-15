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
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <shape.h>
#include <utils.h>
#include <mesh.h>
#include <symbol.h>
#include <sentence.h>

const uint16_t LED_PIN = 5;
const uint32_t I2C_CLOCK = 1000000;
/**
 * @brief
 * This class is responsible for controlling the galvo motors and led.
 * The class is a "singleton" meaning there can only be one instance of this class at a time
 * This allows the class to be called for anywhere in the code
 *
 */
class Pointer
{
private:
    Adafruit_MCP4725 xdim;
    Adafruit_MCP4725 ydim;

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
    void point_to(Vec2 pos);

    /**
     * @brief Moves the pointer towards the provided pos at a given speed, helpful if you want
     * longer and exaggerated lines
     * @param pos
     */
    void move_towards(Vec2 pos, uint16_t delay_time);
    /**
     * @brief toggle_led toggles the current state of the led
     */
    void toggle_led();
    /**
     * @brief toggle_led turns the led to the given state
     * @example HIGH(1) -> on : LOW(0) -> OFF
     * @param state
     */
    void toggle_led(int8_t state);

    // Singleton Constructors
    // only be one
    // These constructors call an error when attempting to copy a pointer instance, as there can
    Pointer(const Pointer &) = delete;
    Pointer(Pointer &&) = delete;
    Pointer &operator=(const Pointer &) = delete;
    Pointer &operator=(Pointer &&) = delete;

    /// @brief Current position of the galvo, updated on point_to()
    Vec2 cur_pos;

    /**
     * @brief Draws a given shape s, the algorithm used depends on the shape's type
     * @param s
     */
    void draw_shape(Shape s);
    void draw_circle(Shape c);
    void draw_rect(Shape s);

    /// @brief Draws a grid of shapes g, default 3x3
    /// @param g
    void draw_grid(Grid g);
    /// @brief Draws a mesh object, these are objects that contain a specific set of vertices to be draw.
    /// This includes characters
    /// @param m
    void draw_mesh(Mesh m);
    /// @brief Draws a symbol object s, if first_word is true, a small delay is added before the laser beings drawing
    /// @param s
    /// @param first_word
    void draw_symbol(Symbol s, bool first_word);
    /// @brief Draws a sentence sen, which is a collection of symbols,
    /// if a sentence goes off screen, it will wrap back below the sentence's orgin
    /// @param sen
    void draw_sentence(Sentence sen);
    // WIP
    void draw_3d_cube(double size, uint16_t x, uint16_t y, uint16_t rows, uint16_t cols);
    /// @brief returns a reference to the singleton instance of this class
    /// @return
    static Pointer &getInstance()
    {
        static Pointer instance;
        return instance;
    }
};

#endif