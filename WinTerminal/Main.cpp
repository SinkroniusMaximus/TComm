#include "Data.h"
#include "../Lib/WinSerial.h"

Data dataSource;
HardwareSerial Serial{"COM1"};
SerialSubscriber serial;

void setup() 
{
    serial.Xinit(&Serial);
    dataSource.cmdMotorSpeed = 100.0f;
}

void loop() 
{
    Communicator.Xchange();
}


int main()
{
    setup();
    while(1)
    {
        loop();
    }
}