#ifndef ABSTRACTCOMMUNICATOR_H
#define ABSTRACTCOMMUNICATOR_H

namespace TComm {

class AbstractCommunicator //Abstract Communication object
{
    public:
        virtual void update(int commIndex) = 0;
        virtual void inject(byte* buffer) = 0;
        virtual String getName() = 0;
        virtual const std::type_info* getType() = 0;
};
};

#endif // ABSTRACTCOMMUNICATOR_H