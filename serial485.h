#ifndef SERIAL485_H
#define SERIAL485_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
class Serial485 : public QObject
{
    Q_OBJECT
public:
    explicit Serial485(QObject *parent = 0);
    ~Serial485();

    bool open_device(QString portNum);
    void read_com();
    void write_com(unsigned char *data, int length);
    void receive(std::vector<unsigned char>& data, const unsigned int bytes);

signals:

public slots:

private:
    QSerialPort *serial;
    unsigned char * receive_data;

};

#endif // SERIAL485_H
