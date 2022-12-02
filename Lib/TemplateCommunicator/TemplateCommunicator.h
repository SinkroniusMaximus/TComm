#ifndef TEMPLATECOMMUNICATOR_H
#define TEMPLATECOMMUNICATOR_H

#include "TComm.h"

template <class T>
class TemplateCommunicator : AbstractCommunicator //Template Communication object
{
    public:
        TemplateCommunicator() 
        { 
            commList.add(this);
        }

        ~TemplateCommunicator() {}

        void Xinit() 
        { 
            
        }

        void Xinit(String input) 
        { 
            commName = input; 
        }

        TemplateCommunicator<T>& operator = (const T& input) 
        { 
            if(!equals(input)) 
            { 
                changed = true; 
                valueOld = input;
                value = input; 
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
                    subList.get(i)->write(CommunicationData{(byte *)&value, sizeof(value), commIndex});
                } // on change iterate through subscribers
                // #ifdef TCommESP32
                //     Serial.println(value);
                // #endif
                // #ifdef TCommWindows
                //     cout << value << "\n";
                // #endif
            } 
        }

        void inject(byte buffer[]) override 
        {
            value = *(T *)buffer; 
            // #ifdef TCommESP32
            //     Serial.print("injected esp: "); Serial.println(value);
            // #endif
            // #ifdef TCommWindows
            //     cout << "injected: " << value << "\n";
            // #endif      
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

#endif //TEMPLATECOMMUNICATOR_H
