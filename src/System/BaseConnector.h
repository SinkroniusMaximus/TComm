#ifndef CONNECTORBASE_H
#define CONNECTORBASE_H

namespace GenericLibrary {

template<typename T>
class BaseConnector {
public:
    BaseConnector() : value(nullptr) {}

    void Connect(T& connection) {
        value = &connection;
    }

    void Disconnect() {
        value = nullptr;
    }
    
    bool IsConnected() {
        return value;
    }

protected:
    T* value;
};

}

#endif // CONNECTORBASE_H