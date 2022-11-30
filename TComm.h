#ifndef TCOMM_H
#define TCOMM_H

#include <Arduino.h>
#include <LinkedPointerList.h>

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
  virtual ~AComm() {}
  virtual void update(int commIndex);
  virtual void inject(byte* buffer);
};

class ASub // Abstract subscription object
{
  public:
  virtual ~ASub() {}
  virtual void write(CommData data);
  virtual void read();
};

static LinkedPointerList<AComm> commList; // Communication object list
static LinkedPointerList<ASub> subList; // Subscriber object list

template <class T>
class TComm : AComm //Template Communication object
{
  public:
    TComm() { }
    void Xinit() { commList.add(this); }
    void Xinit(String input) { commList.add(this); commName = input; }
    TComm<T>& operator = (const T& input) { if(!equals(input)) { changed = true; valueOld = value = input; } return *this; }
    operator T&(){ return value; }
    void set(T input) { if(!equals(input)) { changed = true; valueOld = value = input; }}
    T get() { return value; }
    void update(int commIndex) override { if(isAccessed()) { if(!equals(valueOld)) { changed = true; valueOld = value; }; }; if(isChanged()) 
    {
      for (int i = 0; i < subList.size(); i=i+1)
      {        
        subList.get(i)->write(CommData{(byte *)&value, sizeof(value), commIndex});
      } // on change iterate through subscribers
      Serial.println(value);
    } }
    void inject(byte buffer[]) override {
      value = *(T *)buffer; 
      Serial.print("injected: "); Serial.println(value);
      }
    T* operator ->() { accessed = true; return &value; }
  private:
    T value;
    T valueOld;
    bool changed;
    bool accessed;
    String commName;
    bool isChanged() { bool isChanged = changed; changed = false; return isChanged; }
    bool isAccessed() { bool isAccessed = accessed; accessed = false; return isAccessed; }
    bool equals( T input) { return value == input; }
};

static class Comm // Communicator 
{
  public:
    void Xchange() { for (i = 0; i < commList.size(); i=i+1) { commList.get(i)->update(i); } // on change write
                     for (i = 0; i < subList.size(); i=i+1) { subList.get(i)->read(); } // read incoming data
                   }
  private:
    int i;
} Comm;

class SerialSub : ASub // Subscription of serial port to the communicator
{
  public:  
    void Xinit(HardwareSerial* newPort) { subList.add(this); port = newPort; }
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
//          Serial.print(String(char(buffer[readIndex])));
//          Serial.print(" ");
//          Serial.println(buffer[readIndex]);
          if (readIndex == 1) { readSize = buffer[0] + (buffer[1] << 8);}// Serial.print("readsize: "); Serial.println(readSize);}
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
