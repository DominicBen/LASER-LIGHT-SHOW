#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

struct ControllerState
{
    // uint8_t buttons; // represented as a byte, 0b0000yaxb
    //      X
    //  Y       A
    //      B
    bool up = 9999;
    bool down = 9999;
    bool left = 9999;
    bool right = 9999;
    bool stick = 9999;
    uint16_t xdim = 9999; // 4095 is far left, 0 is far right center is about 1788
    uint16_t ydim = 9999; // 4095 is far up, 0 is far down, 1788 is about middle
};
class Controller
{
private:
    /* data */
public:
    SoftwareSerial ControlerSerial = SoftwareSerial(34, 35); // RX | TX

    String BTADDR = "943c,c6,38818e";

    // bool pair();
    void delayAndRead(int delayTime);
    ControllerState read();

    Controller(String BLTAdress) : BTADDR(BLTAdress){};
    Controller(int rx, int tx)
    {
        Serial.begin(9600);
        ControlerSerial = SoftwareSerial(rx, tx);
        Serial.println("Enter AT commands:");
        ControlerSerial.begin(9600); // HC-05 default speed in AT command more
    };

    ~Controller(){};
};