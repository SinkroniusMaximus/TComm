#ifndef WINSERIAL_H
#define WINSERIAL_H
    #include "WinCommon.h"
namespace TComm
{   
    class HardwareSerial
    {
        public:
            HardwareSerial() {}
            ~HardwareSerial()
            {
                CloseHandle(serialHandle);
            }

            void begin(String comPort, DWORD baudrate)
            {
                begin(comPort, baudrate, 8, TWOSTOPBITS, NOPARITY);
            }

            void begin(String comPort, DWORD baudrate, BYTE byteSize, BYTE stopBits, BYTE parity)
            {
                CloseHandle(serialHandle);
                std::cout << "opening serialport " << ("\\\\.\\" + comPort).c_str() << "\n"; 
                serialHandle = CreateFileA(("\\\\.\\" + comPort).c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                if(serialHandle==INVALID_HANDLE_VALUE)
                {
                    if(GetLastError()==ERROR_FILE_NOT_FOUND)
                    {
                        std::cout << "serial port not found.\n";
                        //serial port not found. Handle error here.
                    }
                    else
                    {
                        //any other error. Handle error here.
                        std::cout << "any other error.\n";
                    }
                }
                // Do some basic settings
                DCB serialParams = { 0 };
                serialParams.DCBlength = sizeof(serialParams);
                if (!GetCommState(serialHandle, &serialParams)) 
                {
                    std::cout << "getcommstate handle error here\n";
                    //handle error here
                }

                // GetCommState(serialHandle, &serialParams);
                serialParams.BaudRate = baudrate;
                serialParams.ByteSize = byteSize;
                serialParams.StopBits = stopBits;
                serialParams.Parity = parity;
                if(!SetCommState(serialHandle, &serialParams))
                {
                    std::cout << "setcommstate handle error here\n";
                    //handle error here
                }
                // Set timeouts
                COMMTIMEOUTS timeout = { 0 };
                timeout.ReadIntervalTimeout = 5;
                timeout.ReadTotalTimeoutConstant = 5;
                timeout.ReadTotalTimeoutMultiplier = 5;
                timeout.WriteTotalTimeoutConstant = 5;
                timeout.WriteTotalTimeoutMultiplier = 1;
                if(!SetCommTimeouts(serialHandle, &timeout))
                {
                    std::cout << "setcommtimeout handle error here\n";
                    //handle error here
                }
                std::cout << "setup comport done\n";
            }

            char read()
            {
                return readBuffer[0];
            }

            bool write(byte* buffer, int size)
            {
                if(!WriteFile(serialHandle, buffer, size, &writeSize, NULL))
                {
                    std::cout << "error nr " << GetLastError() << "\n";
                }
                return ((int)writeSize == size);
            }
            
            int available()
            {
                if(!ReadFile(serialHandle, readBuffer, sizeof(readBuffer), &readSize, NULL))
                {
                    std::cout << "error nr " << GetLastError() << "\n";
                }
                return (int)readSize;
            }
        private:
            // Open serial port
            HANDLE serialHandle;
            byte readBuffer[1];
            DWORD readSize;
            DWORD writeSize;
    };
};
#endif //WINSERIAL_H
