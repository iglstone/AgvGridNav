#ifndef CSERIAL_H
#define CSERIAL_H


//class CSerial
//{
//public:
//    CSerial();
//};

#pragma once
#include <windows.h>

class CSerial
{
public:
    CSerial(void);
    ~CSerial(void);

    //打开串口
    BOOL OpenSerialPort(TCHAR* port, UINT baud_rate, BYTE date_bits, BYTE stop_bit, BYTE parity = NOPARITY);

    //发送数据
    BOOL SendData(char* data, int len);
public:
    HANDLE m_hComm;
};

#endif // CSERIAL_H
