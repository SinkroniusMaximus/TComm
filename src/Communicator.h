#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

namespace TComm {

static class Communicator // Communicator 
{
    public:
        void Xchange() 
        { 
            for (i = 0; i < commList.size(); i=i+1) 
            { 
                // commList.get(i)->update(i); 
                commList.at(i)->update(i);
            } // on change write
            for (i = 0; i < subList.size(); i=i+1) 
            { 
                // subList.get(i)->read(); 
                subList.at(i)->read();
            } // read incoming data
        }
    private:
        int i;
} Communicator;
};

#endif //COMMUNICATOR
