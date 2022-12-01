#ifndef ABSTRACTSUBSCRIBER_H
#define ABSTRACTSUBSCRIBER_H

#include "TComm.h"

class AbstractSubscriber // Abstract subscription object
{
    public:
        virtual void write(CommunicationData data) = 0;
        virtual void read() = 0;
};

#endif // ABSTRACTSUBSCRIBER_H