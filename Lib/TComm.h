#ifndef TCOMM_H
#define TCOMM_H

#ifdef TCommArduino
  #include <Arduino.h>
  #include <LinkedPointerList.h>
#endif

#ifdef TCommWindows
  #include "WinCommon.h"
  #include "WinSerial.h"
  #include "LinkedPointerList\LinkedPointerList.h"
#endif

struct CommData
{
public:
    byte* buffer;
    int size;
    int commIndex;
    void PacketGen(byte out[])
    {
        //format: [size, index, data bytes, null char]
        memcpy(out, &size, 2); // 0,1
        memcpy((out + 2), &commIndex, 2); //2,3
        memcpy((out + 4), buffer, size); // size:4 -> 4,5,6,7
        out[size + 4] = 255; // 8
    };
};

class AComm //Abstract Communication object
{
    public:
        // virtual ~AComm() = 0;
        virtual void update(int commIndex) = 0;
        virtual void inject(byte* buffer) = 0;
};

class ASub // Abstract subscription object
{
    public:
        // virtual ~ASub();
        virtual void write(CommData data) = 0;
        virtual void read() = 0;
};

static LinkedPointerList<AComm> commList; // Communication object list
static LinkedPointerList<ASub> subList; // Subscriber object list

template <class T>
class TComm : AComm //Template Communication object
{
    public:
        TComm() 
        { 
            commList.add(this);
        }
        ~TComm() {}
        void Xinit() 
        { 
            
        }

        void Xinit(String input) 
        { 
            commName = input; 
        }

        TComm<T>& operator = (const T& input) 
        { 
            if(!equals(input)) 
            { 
                changed = true; 
                valueOld = value = input; 
            } 
            return *this;
        }
        operator T&()
        { 
            return value; 
        }
        void set(T input) 
        { 
            if(!equals(input)) 
            { 
                changed = true; 
                valueOld = input; 
                value = input;
            }
        }
        T get() 
        { 
            return value;
        }
        void update(int commIndex) override 
        { 
            if(isAccessed()) 
            { 
                if(!equals(valueOld)) 
                { 
                    changed = true; 
                    valueOld = value; 
                } 
            } 
            if(isChanged()) 
            {
                for (int i = 0; i < subList.size(); i=i+1)
                {        
                    subList.get(i)->write(CommData{(byte *)&value, sizeof(value), commIndex});
                } // on change iterate through subscribers
                #ifdef TCommArduino
                    Serial.println(value);
                #endif
                #ifdef TCommWindows
                    cout << value << "\n";
                #endif
            } 
        }
        void inject(byte buffer[]) override 
        {
            value = *(T *)buffer; 
            #ifdef TCommArduino
                Serial.print("injected: "); Serial.println(value);
            #endif
            #ifdef TCommWindows
                cout << "injected: " << value << "\n";
            #endif      
        }
        T* operator ->() 
        { 
            accessed = true; 
            return &value; 
        }
        private:
        T value;
        T valueOld;
        bool changed;
        bool accessed;
        String commName;
        bool isChanged() 
        { 
            bool isChanged = changed;
            changed = false; 
            return isChanged; 
        }
        bool isAccessed() 
        { 
            bool isAccessed = accessed;
            accessed = false;
            return isAccessed; 
        }
        bool equals( T input) 
        { 
            return value == input;
        }
};

static class Comm // Communicator 
{
    public:
        void Xchange() 
        { 
            for (i = 0; i < commList.size(); i=i+1) 
            { 
                commList.get(i)->update(i); 
            } // on change write
            for (i = 0; i < subList.size(); i=i+1) 
            { 
                subList.get(i)->read(); 
            } // read incoming data
        }
    private:
        int i;
} Comm;

class SerialSub : ASub // Subscription of serial port to the communicator
{
    public:  
        void Xinit(HardwareSerial* newPort) 
        { 
            subList.add(this); 
            port = newPort; 
        }
        void write(CommData data) override { 
        byte toSend[data.size + 5];
        data.PacketGen(toSend);
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

#endif //TCOMM_H
