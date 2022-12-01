#ifndef TCOMM_H
#define TCOMM_H

#ifdef TCommESP32
    #define TCommArduino
#endif

#ifdef TCommArduino
  #include <Arduino.h>
  #include <LinkedPointerList.h>
#endif

#ifdef TCommWindows
  #include "..\WinCommon.h"
  #include "..\WinSerial.h"
  #include "..\LinkedPointerList\LinkedPointerList.h"
#endif

#include "CommunicationData.h"
#include "AbstractCommunicator.h"
#include "AbstractSubscriber.h"

static LinkedPointerList<AbstractCommunicator> commList; // Communication object list
static LinkedPointerList<AbstractSubscriber> subList; // Subscriber object list

#include "TemplateCommunicator.h"
#include "Communicator.h"
#include "SerialSubscriber.h"

#endif //TCOMM_H