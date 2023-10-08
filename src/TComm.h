#ifndef TCOMM_H
#define TCOMM_H


#ifdef TCommESP32
    #define TCommArduino
#endif

#ifdef TCommArduino
  #include <Arduino.h>
#endif

#ifdef TCommWindows
  #include "Windows\WinCommon.h"
  #include "Windows\WinSerial.h"
#endif


#include "CommunicationData.h"
#include "AbstractCommunicator.h"
#include "AbstractSubscriber.h"

#include <typeinfo>
#include <vector>

namespace TComm
{
  static std::vector<AbstractCommunicator*> commList; // Communication object list
  static std::vector<AbstractSubscriber*> subList; //  Subscriber object list
};
#include "TemplateCommunicator.h"
#include "Communicator.h"
#include "ByteSerializer.h"
#include "SerialSubscriber.h"
using namespace TComm;

#endif //TCOMM_H