#include <controller.h>

// bool Controller::pair()
// {
//     // pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
//     // digitalWrite(9, HIGH);
//     Serial.begin(115200);
//     Serial.println("Enter AT commands:");
//     BTSerial.begin(38400); // HC-05 default speed in AT command more

//     BTSerial.println("AT+ORGL"); // reset
//     delayAndRead(100);
//     BTSerial.println("AT+ROLE=1"); // set to master
//     delayAndRead(100);
//     BTSerial.println("AT+RESET"); // clear mem
//     delayAndRead(100);
//     BTSerial.println("AT+INIT"); // initialize
//     delayAndRead(100);
//     BTSerial.println("AT+INQ"); // MAC adddress
//     delayAndRead(1000);
//     Serial.println("bind");
//     BTSerial.println("AT+BIND=" + BTADDR); // bind
//     delayAndRead(1000);
//     Serial.println("pair");
//     BTSerial.println("AT+PAIR=" + BTADDR + ",20"); // controller 1 MAC, 20 second timeout
//     delay(15000);                                  // paring takes a long time
//     delayAndRead(5000);
//     Serial.println("link");
//     BTSerial.println("AT+LINK=" + BTADDR); // connect
//     delayAndRead(1000);
//     BTSerial.println("AT+STATE"); // start data stream
//     return true;
// }

void Controller::delayAndRead(int delayTime)
{
    delay(delayTime);

    while (ControlerSerial.available())
        Serial.write(ControlerSerial.read());
}
ControllerState Controller::read()
{
    ControllerState state;
    // while (BTSerial.available())
    //     Serial.write(BTSerial.read());
    // Serial.println("reading player input");
    while (ControlerSerial.available())
    {
        // Serial.println("READ");
        delay(3);
        // delay(30);

        // delay(30);
        ControlerSerial.readStringUntil('\n');
        ControlerSerial.readStringUntil('\n');

        int buttons = ControlerSerial.parseInt();
        int xdim = ControlerSerial.parseInt();
        int ydim = ControlerSerial.parseInt();
        if (buttons > 32)
            continue;
        // while (ControlerSerial.available())
        //     ControlerSerial.read();

        // Serial.println("buttons " + (String)buttons + "\txdim " + (String)xdim + "\tydim " + (String)ydim);
        // 0b0000yaxb
        int upmask = 1;         // up
        int downmask = 1 << 1;  // down
        int leftmask = 1 << 2;  // left
        int rightmask = 1 << 3; // right
        int stickmask = 1 << 4; // joystick

        state.xdim = xdim;
        state.ydim = ydim;
        // state.buttons = buttons;
        state.up = upmask & buttons;
        state.left = leftmask & buttons;
        state.right = rightmask & buttons;
        state.down = downmask & buttons;
        state.stick = stickmask & buttons;

        // Serial.println("left " + (String)state.left + "right " + (String)state.right + "up " + (String)state.up + "down " + (String)state.down + " xdim  " + (String)xdim + " ydim " + (String)ydim);
        return state;

        // }
    }
    return state;
}
