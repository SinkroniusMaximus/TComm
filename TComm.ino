#include "TComm.h"

struct student {
  bool gender;
  String name;
  int age;
  int grade;
};

typedef TComm<int> Xint;
typedef TComm<float> Xfloat;
typedef TComm<String> Xstring;
typedef TComm<bool> Xbool;
typedef TComm<student> Xstudent;

List<Xint> Xintlist;
List<Xfloat> Xfloatlist;
List<Xstring> Xstringlist;
List<Xbool> Xboollist;
List<Xstudent> Xstudentlist;

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Started");
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
  test11 = 20320;
  test12 = 25;
  test13 = 300;
  test14 = 245;
  test15 = 232;
  test21 = true;
  test22 = false;
  test31 = "hello world";
  test32 = "real time";
  test41 = 123.456;
  test42 = 69.69;
  test5[0] = { false, "kenton", 22, 1 };
  test5[1] = { true, "jenny", 24, 3 };
  test5[2] = { false, "winston", 23, 4 };
  test5[3] = { true, "heater", 19, 2 };
  test5[4] = { false, "chang", 20, 3 };
  test5[5] = { false, "donny", 23, 2 };
  test5[6] = { true, "joan", 25, 3 };
  test5[7] = { false, "andy", 22, 2 };
  test5[8] = { false, "mike", 23, 4 };
  test5[9] = { false, "leo", 20, 2 };
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i = 0; i < Xintlist.size(); i=i+1)
    {
      Xint* value = Xintlist.get(i);
      if(value->isChanged())
      {
        Serial.print("changed: ");
        int val = *value;
        Serial.println(val);
      }
    }
    for (int i = 0; i < Xboollist.size(); i=i+1)
    {
      Xbool* value = Xboollist.get(i);
      if(value->isChanged())
      {
        Serial.print("changed: ");
        bool val = *value;
        Serial.println(val);
      }
    }
    for (int i = 0; i < Xstringlist.size(); i=i+1)
    {
      Xstring* value = Xstringlist.get(i);
      if(value->isChanged())
      {
        Serial.print("changed: ");
        String val = *value;
        Serial.println(val);
      }
    }
    for (int i = 0; i < Xfloatlist.size(); i=i+1)
    {
      Xfloat* value = Xfloatlist.get(i);
      if(value->isChanged())
      {
        Serial.print("changed: ");
        float val = *value;
        Serial.println(val);
      }
    }
    for (int i = 0; i < Xstudentlist.size(); i=i+1)
    {
      Xstudent* value = Xstudentlist.get(i);
      if(value->isChanged())
      {
        Serial.println("changed: ");
        student val = *value;
        Serial.print("gender: ");
        Serial.println(val.gender ? "female" : "male");
        Serial.println("name: " + val.name);
        Serial.print("age: ");
        Serial.println(val.age);
        Serial.print("grade: ");
        Serial.println(val.grade);
      }
    }
  }
