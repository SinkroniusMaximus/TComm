#ifndef SERIALSUBSCRIBER_H
#define SERIALSUBSCRIBER_H

#include "TComm.h"

class SerialSubscriber : AbstractSubscriber // Subscription of serial port to the communicator
{
    public:  
        void Xinit(HardwareSerial* newPort) 
        { 
            subList.add(this); 
            port = newPort; 
        }

        void PacketGen(CommunicationData data, byte out[])
        {
            //format: [size, index, data bytes, null char]
            memcpy(out, &data.size, 2); // 0,1
            memcpy((out + 2), &data.commIndex, 2); //2,3
            memcpy((out + 4), data.buffer, data.size); // size:4 -> 4,5,6,7
            out[data.size + 4] = 255; // 8
        };

        void write(CommunicationData data) override 
        { 
            byte toSend[data.size + 5];
            PacketGen(data, toSend);
            port->write(toSend, sizeof(toSend));
        }
        
        void read() override 
        {       
            if(port->available())
            {
                buffer[readIndex] = port->read();
                if (readIndex == 1) 
                { 
                    readSize = buffer[0] + (buffer[1] << 8);
                }
                if (readIndex == (readSize + 4))
                {
                    if(buffer[readIndex] == 255) // a completed message
                    {
                        commIndex = buffer[2] + (buffer[3] << 8);
                        commList.get(commIndex)->inject(buffer + 4);              
                    }
                // either the message completed or failed, reset the index and receive the next message
                readIndex = 0; 
                }
                else if(buffer[readIndex] == 255) // a completed message
                {
                    readIndex = 0;              
                }
                else
                {
                    readIndex++;
                }
            }
        }
    private:
        HardwareSerial* port;
        byte buffer[512];
        int readIndex;
        int readSize;
        int commIndex;
};

#endif //SERIALSUBSCRIBER