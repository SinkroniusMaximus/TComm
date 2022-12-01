#include "Data.h"
#include "../Lib/WinSerial.h"

Data dataSource;
HardwareSerial Serial{"COM1"};
SerialSub serial;

void setup() 
{
    serial.Xinit(&Serial);
    dataSource.cmdMotorSpeed = 100.0f;
}

void loop() 
{
    Comm.Xchange();
}


int main()
{
    setup();
    while(1)
    {
        loop();
    }
}