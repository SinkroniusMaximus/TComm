#ifndef COMMUNICATIONDATA_H
#define COMMUNICATIONDATA_H

namespace TComm {
    class CommunicationData
    {
    public:
        byte* buffer;
        int size;
        int commIndex;
    };
};

#endif //COMMUNICATIONDATA_H