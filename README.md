# TComm

Here is a new communication protocol in the making.
It is based on a template file that will allow communication of the standard data types like bool, int, float, string for example.
Communication is lightweight since it is based on sending bytes back and forth over the communication channels.
In contrary to the previous communication sketches on my github which used strings to communicate.
It is also possible to design multiple communication subscribers to hook into the variables to be communicated.

Goals:
- a generic communication protocol
- ease of use in the user code
- no need to understand the protocol, once its finished that is
- usage is much like a basic data types
- communication between several platforms that support c++, like windows, linux, arduino or other RTOS devices
- ease of use with different communication channels like serial, bluetooth, wifi, tcp or locally much like IPC.


