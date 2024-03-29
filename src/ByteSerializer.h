#ifndef BYTESERIALIZER_H
#define BYTESERIALIZER_H

namespace TComm {
class ByteSerializer
{
    public:
        ByteSerializer()
        {
            readIndex = 0;
            deviceIndex = 0;
            dataSize = 0;
            commIndex = 0;
        }
        void Serialize(CommunicationData data, byte out[])
        {
            //format: [startKey, deviceIndex, size, commIndex, data bytes]
            uint16_t startKey = 0xDBFB;
            uint16_t devIndex = 0x1;            // todo create variable deviceIndex
            memcpy(out, &startKey, 2); // 0,1
            memcpy((out + 2), &devIndex, 2); // 2,3
            memcpy((out + 4), &data.size, 2); // 4,5
            memcpy((out + 6), &data.commIndex, 2); //6,7
            memcpy((out + 8), data.buffer, data.size); // size:4 -> 8,9,10,11
        };
        void Deserialize(byte read)
        {
            //store a byte
            buffer[readIndex] = read;
            //confirm the startKey is correct
            if(readIndex == 0 && buffer[0] != 0xFB
               || readIndex == 1 && buffer[1] != 0xDB) 
            {
                readIndex = 0;
                return;
            }
            //store the deviceIndex
            if(readIndex == 3) 
            { 
                deviceIndex = buffer[2] + (buffer[3] << 8);
            }
            //store the size of the data
            if(readIndex == 5)
            {
                dataSize = buffer[4] + (buffer[5] << 8);
            }
            //store the list index of the communicated data
            if(readIndex == 7)
            {
                commIndex = buffer[6] + (buffer[7] << 8);
            }
            //relay and inject the completed message
            if(readIndex == (dataSize + 7))
            {
                //todo check if the deviceIndex belongs to this device
                // commList.get(commIndex)->inject(buffer + 8);
                commList.at(commIndex)->inject(buffer + 8);
                //todo or otherwise relay the raw message to the subscriber list
                readIndex = 0;
                return;
            }
            readIndex++;
        }
    private:
        byte buffer[512];
        uint16_t readIndex;
        uint16_t deviceIndex;
        uint16_t dataSize;
        uint16_t commIndex;
}; 
};

#endif //BYTESERIALIZER_H
