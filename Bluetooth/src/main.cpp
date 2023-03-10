#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(7, 8); // RX | TX

void sendCommand(const char *command)
{
  Serial.print("Command send :");
  Serial.println(command);
  BTSerial.println(command);
  // wait some time
  delay(100);

  char reply[10000];
  int i = 0;
  while (BTSerial.available())
  {
    reply[i] = BTSerial.read();
    i += 1;
  }
  // end the string
  reply[i] = '\0';
  Serial.print(reply);
  // delay(1000);
}

void readSerial()
{
  // delay(400);
  char reply[50000];
  int i = 0;
  while (BTSerial.available())
  {
    reply[i] = BTSerial.read();
    i += 1;
    // delay(1);
  }

  // end the string
  reply[i] = '\0';
  if (strlen(reply) > 0)
  {
    Serial.print(reply);
    // Serial.println("We have just read some data");
  }
}

void printBTInformation()
{
  sendCommand("AT+VERSION");
}

void setup()
{
  // pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  // digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600); // HC-05 default speed in AT command more
  delay(3000);
  // printBTInformation();
  // sendCommand("AT+RMAAD");               // clear active clients
  // sendCommand("AT+CMODE=0");
  delay(400); // Connect to controller
  // sendCommand("AT+HELP");
  // sendCommand("AT+ROLE1"); // Set as master
  // sendCommand("AT+VERSION");
  // sendCommand("AT+IMME1");
  // sendCommand("AT+CON30317D05055F"); // bind to controller
  sendCommand("AT+NAMELaserLightShow");
  delay(500);
  sendCommand("AT+ROLE1"); // bind to controller
  delay(500);
  sendCommand("AT+CONA"); // bind to controller
  delay(500);
  // sendCommand("AT+INQ"); // bind to controller
  // delay(500);

  // sendCommand("AT+INQ"); // bind to controller
  // delay(500);
  // sendCommand("AT+INQ"); // bind to controller
  // delay(500);
  // sendCommand("AT+INQ"); // bind to controller
  // delay(500);
  // sendCommand("AT+LADDR"); // bind to controller
  // delay(500);
  // sendCommand("AT+HELP");
  // readSerial();

  // readSerial();
}

void loop()
{
  sendCommand("AT+INQ"); // bind to controller
  delay(500);
  for (size_t i = 0; i < 100; i++)
  {
    /* code */
    readSerial();
    delay(50);
  }
  delay(1000);
  // delay(3);
  // sendCommand("AT+CON30317D05055F"); // bind to controller

  // Serial.println("Reply end");
  // // Keep reading from HC-05 and send to Arduino Serial Monitor

  // if (BTSerial.available())
  // {
  //   // Serial.println("bt available...");
  //   Serial.write(BTSerial.read());
  // }

  // // Keep reading from Arduino Serial Monitor and send to HC-05
  // if (Serial.available())
  //   BTSerial.println("AT");
}
