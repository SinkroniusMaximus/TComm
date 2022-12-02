#define TCommArduino
#include "Data.h"

Data dataSource;
SerialSubscriber serial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  serial.Xinit(&Serial);
}

void loop() 
{
    Communicator.Xchange();
    dataSource.stsMotorSpeed = (float)dataSource.cmdMotorSpeed;
    dataSource.stsMotorRun = (bool)dataSource.cmdRunMotor;
}
