#ifndef TEMPLATECOMMUNICATOR_H
#define TEMPLATECOMMUNICATOR_H

namespace TComm {
template <class T>
class TemplateCommunicator : AbstractCommunicator //Template Communication object
{
    public:
        TemplateCommunicator() 
        { 
            commList.push_back(this);
        }
        TemplateCommunicator(String name) 
        { 
            commList.push_back(this);
            commName = name;
        }
        TemplateCommunicator(String name, String* path) 
        { 
            commList.push_back(this);
            commName = name;
            commPath = path;
        }

        ~TemplateCommunicator() {}

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
                    // subList.get(i)->write(CommunicationData{(byte *)&value, sizeof(value), commIndex});
                    subList.at(i)->write(CommunicationData{(byte *)&value, sizeof(value), commIndex});
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
            //     cout << "injected: " << commName << " " << value << "\n";
            // #endif      
        }

        T* operator ->() 
        { 
            accessed = true; 
            return &value; 
        }
        String getName()
        {
            return commName;
        }

        void setName(String name)
        {
            commName = name;
        }

        const std::type_info* getType()
        {
            return &typeid(T);
        }

    private:
        T value;
        T valueOld;
        bool changed;
        bool accessed;
        String commName;
        String* commPath;

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
};

#endif //TEMPLATECOMMUNICATOR_H
