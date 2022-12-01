#ifndef ABSTRACTCOMMUNICATOR_H
#define ABSTRACTCOMMUNICATOR_H

class AbstractCommunicator //Abstract Communication object
{
    public:
        virtual void update(int commIndex) = 0;
        virtual void inject(byte* buffer) = 0;
};

#endif // ABSTRACTCOMMUNICATOR_H