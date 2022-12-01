#define TCommArduino
#include "TComm.h"

typedef TComm<int> Xint;
typedef TComm<float> Xfloat;
typedef TComm<const char*> Xstring;
typedef TComm<bool> Xbool;

Xint test11;
Xint test12;
Xint test13;
Xint test14;
Xint test15;
Xbool test21;
Xbool test22;
Xstring test31;
Xstring test32;
Xfloat test41;
Xfloat test42;

SerialSub serial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  serial.Xinit(&Serial2);
  test11 = 505;//20320;
  test12 = 202;//25;
  test13 = 300;
  test14 = 245;
  test15 = 232;
  test21 = true;
  test22 = false;
  test31 = "hello world";
  test32 = "real time";
  test41 = 123.456;
  test42 = 69.69;
}

void loop() 
{
    Comm.Xchange();
}
