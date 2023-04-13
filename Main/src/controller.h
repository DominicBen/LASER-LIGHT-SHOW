#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

struct ControllerState
{
    // uint8_t buttons; // represented as a byte, 0b0000yaxb
    //      X
    //  Y       A
    //      B
    bool up = 0;
    bool down = 0;
    bool left = 0;
    bool right = 0;
    bool stick = 0;
    bool upIsPressed = 0;
    bool downIsPressed = 0;
    bool leftIsPressed = 0;
    bool rightIsPressed = 0;
    bool stickIsPressed = 0;
    uint16_t xdim = 512;  // 4095 is far left, 0 is far right center is about 1788
    uint16_t ydim = 512;  // 4095 is far up, 0 is far down, 1788 is about middle
    bool isValid = false; // Weather an input is valid or not
    bool operator==(const ControllerState &other) const
    {
        return (up == other.up &&
                down == other.down &&
                left == other.left &&
                right == other.right &&
                stick == other.stick &&
                xdim == other.xdim &&
                ydim == other.ydim);
    }
};

class Controller
{
private:
    /* data */
public:
    SoftwareSerial ControlerSerial;

    String BTADDR = "943c,c6,38818e";
    ControllerState mPreviousInput;
    int mControllerDeadzone = 100;

    // bool pair();
    void delayAndRead(int delayTime);
    ControllerState read();

    Controller(int rx, int tx) : ControlerSerial(SoftwareSerial(rx, tx))
    {
        Serial.begin(9600);
        Serial.println("Enter AT commands:");
        ControlerSerial.begin(9600); // HC-05 default speed in AT command more
    };

    ~Controller(){};
};