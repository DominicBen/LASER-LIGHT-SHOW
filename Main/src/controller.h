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
    uint16_t xdim = 9999; // 4095 is far left, 0 is far right center is about 1788
    uint16_t ydim = 9999; // 4095 is far up, 0 is far down, 1788 is about middle
};
class Controller
{
private:
    /* data */
public:
    SoftwareSerial BTSerial = SoftwareSerial(28, 29); // RX | TX

    String BTADDR = "943c,c6,38818e";

    bool pair();
    void delayAndRead(int delayTime);
    ControllerState read();

    Controller(String BLTAdress);
    ~Controller();
};

Controller::Controller(String BLTAdress)
{
    BTADDR = BLTAdress;
}

Controller::~Controller()
{
}
bool Controller::pair()
{
    // pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
    // digitalWrite(9, HIGH);
    Serial.begin(115200);
    Serial.println("Enter AT commands:");
    BTSerial.begin(38400); // HC-05 default speed in AT command more

    BTSerial.println("AT+ORGL"); // reset
    delayAndRead(100);
    BTSerial.println("AT+ROLE=1"); // set to master
    delayAndRead(100);
    BTSerial.println("AT+RESET"); // clear mem
    delayAndRead(100);
    BTSerial.println("AT+INIT"); // initialize
    delayAndRead(100);
    BTSerial.println("AT+INQ"); // MAC adddress
    delayAndRead(1000);
    Serial.println("bind");
    BTSerial.println("AT+BIND=" + BTADDR); // bind
    delayAndRead(1000);
    Serial.println("pair");
    BTSerial.println("AT+PAIR=" + BTADDR + ",20"); // controller 1 MAC, 20 second timeout
    delay(15000);                                  // paring takes a long time
    delayAndRead(5000);
    Serial.println("link");
    BTSerial.println("AT+LINK=" + BTADDR); // connect
    delayAndRead(1000);
    BTSerial.println("AT+STATE"); // start data stream
    return true;
}

void Controller::delayAndRead(int delayTime)
{
    delay(delayTime);

    while (BTSerial.available())
        Serial.write(BTSerial.read());
}
ControllerState Controller::read()
{
    ControllerState state;
    // while (BTSerial.available())
    //     Serial.write(BTSerial.read());
    while (BTSerial.available())
    {
        delay(3);
        // delay(30);

        // delay(30);
        BTSerial.readStringUntil('\n');
        BTSerial.readStringUntil('\n');

        int buttons = BTSerial.parseInt();
        int xdim = BTSerial.parseInt();
        int ydim = BTSerial.parseInt();
        if (buttons > 15)
            continue;
        while (BTSerial.available())
            BTSerial.read();

        Serial.println("buttons " + (String)buttons + "\txdim " + (String)xdim + "\tydim " + (String)ydim);
        // 0b0000yaxb
        int downmask = 1;
        int upmask = 1 << 1;
        int rightmask = 1 << 2;
        int leftmask = 1 << 3;

        state.xdim = xdim;
        state.ydim = ydim;
        // state.buttons = buttons;
        state.up = upmask & buttons;
        state.left = leftmask & buttons;
        state.right = rightmask & buttons;
        state.down = downmask & buttons;

        Serial.println("left " + (String)state.left + "right " + (String)state.right + "up " + (String)state.up + "down " + (String)state.down + " xdim  " + (String)xdim + " ydim " + (String)ydim);
        return state;

        //     // char cur_char = (char)BTSerial.read();
        //     // if (cur_char = '\n')
        //     // {
        //     //     while (1)
        //     //     {

        //     //         char cur_char = (char)BTSerial.readline();
        //     //         if (cur_char == '\n')
        //     //         {
        //     //             break;
        //     //         }
        //     //         else if (cur_char)
        //     //         {
        //     //             Serial.write((int)cur_char);
        //     //         }

        //     //         /* code */
        //     //     }
        //     //     Serial.println("===============");
        //     //     // Serial.println("");
        //     //     delay(1000);
        //     // }
        // }
    }
    return state;
}
