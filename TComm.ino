#include "TComm.h"

struct Student 
{
  const char* name;
  int age;
  bool gender;
  int grade;
  bool operator == ( Student& right) { return (name == right.name) && (age == right.age) && (gender == right.gender) && (grade == right.grade); }
  operator String() { return "name: " + String(name) + " age: " + String(age) + " gender: " + (gender ? "female" : "male") + " grade: " + grade; }
};


typedef TComm<int> Xint;
typedef TComm<float> Xfloat;
typedef TComm<const char*> Xstring;
typedef TComm<bool> Xbool;
typedef TComm<Student> Xstudent;

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
Xstudent test5[10];

SerialSub serial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  serial.Xinit(&Serial2);
//  Serial.println("Started");
  test11.Xinit();
  test12.Xinit();
  test13.Xinit();
  test14.Xinit();
  test15.Xinit();
  test21.Xinit();
  test22.Xinit();
  test31.Xinit();
  test32.Xinit();
  test41.Xinit();
  test42.Xinit();
  for(int i = 0; i < 10; i++)
  {
    test5[i].Xinit();
  }
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
  test5[0] = { "kenton", 22, false, 1 };
  test5[1] = { "jenny", 24, true, 3 };
  test5[2] = { "winston", 23, false, 4 };
  test5[3] = { "heater", 19, true, 2 };
  test5[4] = { "chang", 20, false, 3 };
  test5[5] = { "donny", 23, false, 2 };
  test5[6] = { "joan", 25, true, 3 };
  test5[7] = { "andy", 22, false, 2 };
  test5[8] = { "mike", 23, false, 4 };
  test5[9] = { "leo", 20, false, 2 };
}

void loop() 
{
    Comm.Xchange();
}
