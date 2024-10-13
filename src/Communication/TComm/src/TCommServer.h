#ifndef TCOMMSERVER_H
#define TCOMMSERVER_H

namespace TComm
{
class TCommServer : public TCommBase
{
public:
    TCommServer()
    {
        // register types, so when receiving device list
        // it can generate a identical list in the server
        TypeRegistry::RegisterType<int>();      // Xint
        TypeRegistry::RegisterType<int32_t>();  // Xint32
        TypeRegistry::RegisterType<uint8_t>();  // Xuint8
        TypeRegistry::RegisterType<uint16_t>(); // Xuint16
        TypeRegistry::RegisterType<float>();    // Xfloat
        TypeRegistry::RegisterType<bool>();     // Xbool
        message;
    }
    void Run()
    {
        // PRINT("server run");
        communicator.Run();
        HandleOverhead();
    }
private:
    void HandleOverhead()
    {
        bool changeReceived = message.type.IsChangeReceived();
        if(changeReceived)
        {
            PRINT("change received");
            ;
        }
        switch(message.type)
        {
            case eNone:
            {
                // PRINT("CCCC");
                if(subjectIsBeingInterrogated)
                {
                    if(interruptedSequence)
                    {
                        message.type = sequenceMessageType;
                        interruptedSequence = false;
                    }
                    else if(subjectDeviceListSize == 0)
                    {
                        // PRINT("CCDD");
                        message.type = eRequestListSize;
                        sequenceMessageType = message.type;
                    }
                    else if(subjectObjectIndex < subjectDeviceListSize)
                    {
                        // PRINT("DDDD");
                        message.value = subjectObjectIndex;
                        message.type = eRequestNameOfObject;
                        sequenceMessageType = message.type;
                    }
                    else
                    {
                        PRINT("choose between end or request all data -------");
                        PRINT((String)sequenceMessageType);
                        PRINT((String)eRequestAllData);
                        if(!(sequenceMessageType == eRequestAllData))
                        {
                            message.type = eRequestAllData;
                            sequenceMessageType = message.type;
                            PRINT("requesting all data");
                        }
                        else
                        {
                            message.type = eEndInterrogation;
                            subjectIsBeingInterrogated = false;
                            PRINT("ending interrogation");
                        }
                    }
                }
                break;
            }
            case eWhatsMyDeviceAddress:
            {
                if(!subjectIsBeingInterrogated)
                {
                    PRINT("whats my device?");
                    PRINT(message.text1->c_str());
                    subjectDeviceIndex = (nrOfEnrolledDevices) + 2;
                    message.value = subjectDeviceIndex;
                    nrOfEnrolledDevices++;
                    subjectIsBeingInterrogated = true;
                    subjectObjectIndex = 0;
                    message.type = eYourDeviceAddressIs;
                }
                else
                {
                    interruptedSequence = true;
                    message.type = ePleaseBePatient;
                }
                break;
            }
            case eYourDeviceAddressIs:
            {
                break;
            }
            case eRequestAllData:
            {
                break;
            }
            case eRequestNameOfObject:
            {
                break;
            }
            case eResponseNameOfObject:
            {
                PRINT("response name");
                // PRINT(message->text);
                if (subjectIsBeingInterrogated) 
                {
                    subjectObjectName = message.text1; 
                    // subjectObjectIndex++;
                    // PRINT("AAAA");
                    message.type = eRequestPathOfObject;
                    sequenceMessageType = message.type;
                    break;
                }
                message.type = eNone;
                // PRINT("BBBB");
                break;
            }
            case eRequestPathOfObject:
            {
                break;
            }
            case eResponsePathOfObject:
            {
                PRINT("response path");
                PRINT(message.text1->c_str());
                if (subjectIsBeingInterrogated) 
                {
                    subjectObjectPath = message.text1;
                }
                message.type = eRequestDataTypeOfObject;
                sequenceMessageType = message.type;
                break;
            }
            case eRequestDataTypeOfObject:
            {
                break;
            }
            case eResponseDataTypeOfObject:
            {
                PRINT("response data type");
                PRINT(message.text1->c_str());
                if(subjectIsBeingInterrogated)
                {
                    TypeRegistry::CreateObject(message.text1->c_str(), subjectDeviceIndex);
                    SetObjectName(subjectDeviceIndex, subjectObjectIndex, subjectObjectName.c_str());
                    SetObjectPath(subjectDeviceIndex, subjectObjectIndex, subjectObjectPath.c_str());

                    int localIndex = GetListSize(subjectDeviceIndex) - 1;
                    // PRINT("got list size");
                    if( localIndex != subjectObjectIndex)
                    {
                        PRINT("Index error");
                        PRINT("subject Device Index");
                        PRINT(String(subjectDeviceIndex));
                        PRINT("local index");
                        PRINT(String(localIndex));
                        PRINT("subject object index");
                        PRINT(String(subjectObjectIndex));
                        while(1)
                        {
                            
                        }
                    }
                    subjectObjectIndex++;
                }
                message.type = eNone;
                sequenceMessageType = message.type;
                break;
            }
            case eRequestObject:
            {         
                break;
            }
            case eResponseObject:
            {
                break;
            }
            case eRequestListSize:
            {
                // PRINT("requesting list size");
                break;
            }
            case eResponseListSize:
            {
                PRINT("response list size");
                PRINT(String(message.value));
                subjectDeviceListSize = message.value;
                message.type = eNone;
                break;
            }
            case eEndInterrogation:
            {
                // PRINT("ended interrogation");
                break;
            }
            case ePleaseBePatient:
            {
                break;
            }
        };
        // PRINT("Finish overhead");
    };
    MESSAGE message{"TComm"};
    std::string subjectObjectName;
    std::string subjectObjectPath;
    uint16_t nrOfEnrolledDevices;
    bool subjectIsBeingInterrogated;
    uint16_t subjectDeviceIndex;
    uint16_t subjectDeviceListSize;
    uint16_t subjectObjectIndex;
    bool interruptedSequence;
    MESSAGETYPE sequenceMessageType;
};
};
#endif //TCOMMSERVER_H