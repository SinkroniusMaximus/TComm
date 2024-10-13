#ifndef BASESUBSCRIBER_H
#define BASESUBSCRIBER_H
namespace TComm
{
class BaseSubscriber : public AbstractSubscriber
{
    public:
        BaseSubscriber()
        {
            communicator.subList.push_back(this);
        }
        const std::type_info* GetObjectType(uint16_t deviceIndex, uint16_t objectIndex)
        {
            return communicator.GetCommunicationObject(deviceIndex, objectIndex)->GetType();
        }
        const char* GetObjectName(uint16_t deviceIndex, uint16_t objectIndex)
        {
            return communicator.GetCommunicationObject(deviceIndex, objectIndex)->GetName();
        }
        const char* GetObjectPath(uint16_t deviceIndex, uint16_t objectIndex)
        {
            return communicator.GetCommunicationObject(deviceIndex, objectIndex)->GetPath();
        }
        const size_t GetObjectDataSize(uint16_t deviceIndex, uint16_t objectIndex)
        {
            return communicator.GetCommunicationObject(deviceIndex, objectIndex)->GetSize();
        }

        const int GetListSize(uint16_t deviceIndex)
        {
            return communicator.GetObjectListSize(deviceIndex);
        }
        void InjectCommObject(CommunicationData commData, AbstractSubscriber* sourceSubscriber)
        {
            communicator.InjectCommObject(commData, sourceSubscriber);
        }
};
};
#endif // BASESUBSCRIBER_H