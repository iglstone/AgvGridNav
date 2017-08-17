#include "serial485.h"

Serial485::Serial485(QObject *parent) : QObject(parent)
{
    this->serial = new QSerialPort;
}

Serial485::~Serial485(){
    this->serial->close();
}

bool Serial485::open_device(QString portNum){

    //even parity check bit, 1 stop bit, 8 data size

    serial->setPortName(portNum);	//设置COM口
    serial->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
    serial->setDataBits(QSerialPort::Data8);		//数据位为8位
    serial->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serial->setParity(QSerialPort::EvenParity);	//even校验位
    serial->setStopBits(QSerialPort::OneStop);	//一位停止位

    serial->close();					//先关串口，再打开，可以保证串口不被其它函数占用。
    if(serial->open(QIODevice::ReadWrite))		//以可读写的方式打开串口
    {
        connect(serial,SIGNAL(readyRead()),this,SLOT(read_Com()));
    }else {
        printf("w t f.. serial open wrong!");
    }

}

void Serial485::read_com()
{
    QByteArray temp = serial->read(1024);//在缓冲区中读1024
    if(!temp.isEmpty())//如果读到的数据不为空
    {
        receive_data = NULL;
        printf(temp);
        receive_data = (unsigned char *)temp.data();
    }
}

void Serial485::receive(std::vector<unsigned char> & data, const unsigned int bytes)
{
    data.resize(bytes);
    data.push_back(*receive_data);
}

void Serial485::write_com(unsigned char *data, int length)
{
    QByteArray arr = QByteArray::fromRawData((char *)data, length);
    serial->write(arr);
}

