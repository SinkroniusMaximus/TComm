#ifndef WINSERIAL_H
#define WINSERIAL_H
    #include "WinCommon.h"
    class HardwareSerial
    {
        public:
            HardwareSerial(String comPort)
            {
                HardwareSerial(comPort, 9600, 8, TWOSTOPBITS, NOPARITY);  
            }

            HardwareSerial(String comPort, DWORD baudrate, BYTE byteSize, BYTE stopBits, BYTE parity)
            {
                serialHandle = CreateFileA(("\\\\.\\" + comPort).c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                // Do some basic settings
                DCB serialParams = { 0 };
                serialParams.DCBlength = sizeof(serialParams);

                GetCommState(serialHandle, &serialParams);
                serialParams.BaudRate = baudrate;
                serialParams.ByteSize = byteSize;
                serialParams.StopBits = stopBits;
                serialParams.Parity = parity;
                SetCommState(serialHandle, &serialParams);

                // Set timeouts
                COMMTIMEOUTS timeout = { 0 };
                timeout.ReadIntervalTimeout = 50;
                timeout.ReadTotalTimeoutConstant = 50;
                timeout.ReadTotalTimeoutMultiplier = 50;
                timeout.WriteTotalTimeoutConstant = 50;
                timeout.WriteTotalTimeoutMultiplier = 10;

                SetCommTimeouts(serialHandle, &timeout);

            }
            ~HardwareSerial()
            {
                CloseHandle(serialHandle);
            }
            char read()
            {
                return readBuffer[0];
            }
            bool write(byte* buffer, int size)
            {
                WriteFile(serialHandle, buffer, size, &writeSize, NULL);
                return ((int)writeSize == size);

            }
            int available()
            {
                ReadFile(serialHandle, readBuffer, sizeof(readBuffer), &readSize, NULL); 
                return (int)readSize;
            }
        private:
            // Open serial port
            HANDLE serialHandle;
            char readBuffer[1];
            DWORD readSize;
            DWORD writeSize;
    };
#endif //WINSERIAL_H
