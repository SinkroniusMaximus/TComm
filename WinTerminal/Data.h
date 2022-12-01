#ifndef DATA_H
#define DATA_H

#define TCommWindows
#include "../Lib/WinCommon.h"
#include "../Lib/TComm.h"

typedef TComm<int> Xint;
typedef TComm<float> Xfloat;
typedef TComm<String> Xstring;
typedef TComm<bool> Xbool;

class Data
{
    public:
        Xbool cmdRunMotor;
        Xfloat cmdMotorSpeed;
        Xbool cmdMotorFast;
        Xbool stsMotorRun;
        Xfloat stsMotorSpeed;
};

#endif // DATA_H