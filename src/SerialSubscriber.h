#ifndef SERIALSUBSCRIBER_H
#define SERIALSUBSCRIBER_H

namespace TComm {

class SerialSubscriber : ByteSerializer, AbstractSubscriber // Subscription of serial port to the communicator
{
    public:  
        void Xinit(HardwareSerial* newPort) 
        { 
            // subList.add(this); 
            subList.push_back(this); 
            port = newPort;
        }

        void write(CommunicationData data) override 
        { 
            byte toSend[data.size + 8];
            Serialize(data, toSend);
            // #ifdef TCommWindows
            //     cout << "data sent: ";
            //     for(int i = 0; i < data.size + 8; i++)
            //     {
            //         cout << (int)toSend[i] << " ";
            //     }
            //     cout << "\n";
            // #endif
            // #ifdef TCommESP32
            //     Serial.print("data sent esp: ");
            //     for(int i = 0; i < data.size + 8; i++)
            //     {
            //         Serial.print((int)toSend[i]);
            //         Serial.print(" ");
            //     }
            //     Serial.println(" ");
            // #endif
            port->write(toSend, sizeof(toSend));
        }
        
        void read() override 
        {
            if(port->available())
            {
                Deserialize(port->read());
            }
        }
    private:
        HardwareSerial* port;
};
};
#endif //SERIALSUBSCRIBER
