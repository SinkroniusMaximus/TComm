#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

namespace TComm {

static class Communicator// Communicator 
{
    friend class ByteSerializer;
    friend class BaseCommunicationObject;
    friend class BaseSubscriber;
    friend class TCommBase;
    public:
        void Run() 
        {
            ReadData();
            UpdateCommObjects();
        }        
        void SetSendAllData()
        {
            sendAllData = true;            
        }
    protected:
        void WriteData(const CommunicationData& commData, AbstractSubscriber* excludedSubscriber = nullptr) 
        {
                // PRINT("write");
                // PRINT("device index ");
                // PRINT(String(commData.deviceIndex));
                // PRINT("object index ");
                // PRINT(String(commData.objectIndex));
                // PRINT("datasize ");
                // PRINT(String(commData.dataSize));
                // PRINT("filterIndex");
                // PRINT(String(filterIndex));
            if(!filterDeviceIndex || (commData.deviceIndex == filterIndex))
            {
                // PRINT("here");
                for (auto& subscriber : subList)
                {
                    if (subscriber != excludedSubscriber)
                    {
                        subscriber->Write(commData);
                    }
                }
            }
            else
            {
                // PRINT("filtered");
            }
        }

        void InjectCommObject(CommunicationData commData, AbstractSubscriber* excludedSubscriber)
        {
                // PRINT("Inject");
                // PRINT("device index ");
                // PRINT(String(commData.deviceIndex));
                // PRINT("object index ");
                // PRINT(String(commData.objectIndex));
                // PRINT("datasize ");
                // PRINT(String(commData.dataSize));
            if(!filterDeviceIndex || (commData.deviceIndex == filterIndex))
            {
                // PRINT("device index " << commData.deviceIndex);
                // PRINT("object index " << commData.objectIndex);
                // PRINT("datasize " << commData.dataSize);
                auto deviceEntry = deviceObjectMap.find(commData.deviceIndex);
                if (deviceEntry != deviceObjectMap.end()) 
                {
                    // PRINT("device found");
                    
                    if(deviceEntry->second.size() > commData.objectIndex)
                    {
                        auto objectEntry = deviceEntry->second.at(commData.objectIndex);
                        // PRINT("object found");
                        objectEntry->Inject(commData.buffer);
                    }
                    else
                    {
                        ;
                        // PRINT("object not found");
                    }
                }
                else
                {
                    // PRINT("device not found");
                    // TODO pass message through to subscribers, message is not meant for this device
                }
                WriteData(commData, excludedSubscriber);
            }
            else
            {
                // PRINT("filtered");
            }
        }

        int AddCommunicationObject(uint16_t deviceIndex, std::shared_ptr<AbstractCommunicationObject> communicationObject)
        {
            deviceObjectMap[deviceIndex].push_back(communicationObject);
            return deviceObjectMap[deviceIndex].size() - 1;
        }

        template<typename T>
        int AddCommunicationObject(uint16_t deviceIndex, T* communicationObject) 
        {
            static_assert(std::is_base_of<AbstractCommunicationObject, T>::value, "T must derive from AbstractCommunicationObject");
            deviceObjectMap[deviceIndex].push_back(std::shared_ptr<AbstractCommunicationObject>(communicationObject, [](T*) {}));
            return deviceObjectMap[deviceIndex].size() - 1;
        }

        std::shared_ptr<AbstractCommunicationObject> GetCommunicationObject(uint16_t deviceIndex, uint16_t objectIndex)
        {
            return deviceObjectMap[deviceIndex].at(objectIndex);
        }
        
        size_t GetObjectListSize(uint16_t deviceIndex)
        {
            return deviceObjectMap[deviceIndex].size();
        }
        void SetDeviceFilter(bool filterDeviceIndex, uint16_t filterIndex)
        {
            this->filterDeviceIndex = filterDeviceIndex;
            this->filterIndex = filterIndex;
        }
        // Updating device index by removing the old key and inserting the new key
        void UpdateDeviceIndex(uint16_t oldDeviceIndex, uint16_t newDeviceIndex) 
        {
            auto deviceEntry = deviceObjectMap.find(oldDeviceIndex);
            if (deviceEntry != deviceObjectMap.end()) 
            {
                const std::vector<std::shared_ptr<AbstractCommunicationObject>>& objectList = deviceEntry->second;
                for (std::shared_ptr<AbstractCommunicationObject> commObject : objectList) 
                {
                    commObject->SetDeviceIndex(newDeviceIndex);

                }
                deviceObjectMap[newDeviceIndex] = std::move(deviceEntry->second);
                deviceObjectMap.erase(deviceEntry);
            }
        }
        std::unordered_map<uint16_t, std::vector<std::shared_ptr<AbstractCommunicationObject>>> deviceObjectMap; // Communication object list per device
        std::vector<AbstractSubscriber*> subList; //  Subscriber object list

    private:
        void ReadData()
        {
            for (i = 0; i < subList.size(); i=i+1) 
            { 
                subList.at(i)->Read(); 
            } // read incoming data
        }

        void UpdateCommObjects()
        {
            for (const auto& deviceEntry : deviceObjectMap) 
            {
                // uint16_t deviceIndex = deviceEntry.first;
                const std::vector<std::shared_ptr<AbstractCommunicationObject>>& objectList = deviceEntry.second;
                for (std::shared_ptr<AbstractCommunicationObject> commObject : objectList) 
                {
                    if(sendAllData)
                    {
                        commObject->SetChanged(); //force sending all data
                    }
                    if(IsTimeToUpdate(commObject->GetUpdateInterval()) || sendAllData)
                    {
                        commObject->Update();
                    }
                }
            } // on change write
            sendAllData = false;
        }

        bool IsTimeToUpdate(EnumUpdateInterval updateInterval)
        {
            switch(updateInterval)
            {
                case eOnChange:
                    return true;
                case eClock_10hz:
                    return clockBits.ClockEdge_10hz();
                case eClock_5hz:
                    return clockBits.ClockEdge_5hz();
                case eClock_2_5hz:
                    return clockBits.ClockEdge_2_5hz();
                case eClock_2hz:
                    return clockBits.ClockEdge_2hz();
                case eClock_1_hz:
                    return clockBits.ClockEdge_1hz();
                case eClock_0_625hz:
                    return clockBits.ClockEdge_0_625hz();
                case eClock_0_5hz:
                    return clockBits.ClockEdge_0_5hz();
            };
            return false;
        }
        int i;
        bool sendAllData;
        bool filterDeviceIndex;
        uint16_t filterIndex;
} communicator;
};

#endif //COMMUNICATOR
