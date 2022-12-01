#ifndef DATA_H
#define DATA_H
#include "TComm.h"

typedef TemplateCommunicator<int> Xint;
typedef TemplateCommunicator<float> Xfloat;
typedef TemplateCommunicator<String> Xstring;
typedef TemplateCommunicator<bool> Xbool;

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
