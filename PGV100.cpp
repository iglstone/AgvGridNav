#include "PGV100.h"
#include <iostream>
#include <QTime>
#include <synchapi.h>

namespace {
const unsigned int BIT_RW = 7;
const unsigned int BIT_ANF0 = 2;
const unsigned int BIT_ANF1 = 3;
const unsigned int BIT_ANF2 = 4;
const unsigned int BIT_ANF3 = 5;
const unsigned int BIT_ANF4 = 6;
}

PGV100::PGV100(Serial485 &bus, const unsigned int id)
: _bus(bus),
    _id(id),
    _positionX(0.0f),
    _positionY(0.0f),
    _angel(0.0f),
    _tagID(0)
{
    std::vector<unsigned char> bytes(2);

    //always send the oxE4(11100100) 1B to pgv100 to chouse the right side
    bytes[0] = ((1 << BIT_RW) | (1 << BIT_ANF4) | (1 << BIT_ANF3) | (1 << BIT_ANF0));//E4
    bytes[1] = ~bytes[0];//1B

    _bus.write_com(bytes.data(), 2);
}

QString PGV100::grab(void)
{
    std::vector<unsigned char> bytes(2);
    //always send the oxC8(11001000) 37 to pgv100 to check the receiver
    bytes[0] = ((1 << BIT_RW) | (1 << BIT_ANF4) | (1 << BIT_ANF1));//C8
    bytes[1] = ~bytes[0];//37
    std::cout << "Bytes[0] : " << std::hex << bytes[0] << std::endl;
    std::cout << "Bytes[1] : " << std::hex << bytes[1] << std::endl;
    //_bus.send(bytes);

    _bus.write_com(bytes.data(), 2);

    Sleep(100);//ms

    _bus.receive(bytes, 21);
    //bytes = {0x0C, 0x05, 0x00, 0x00, 0x36, 0x6B, 0x00, 0x19, 0x00, 0x00, 0x01, 0x2E, 0x00, 0x00, 0x10, 0x0A, 0x00, 0x00, 0x00, 0x04, 0x7C};

    /*
    if((bytes[0] & 0x1)){
      std::cout << "something error.." <<std::endl;
      return;
    }
    if((bytes[0] & 0x4)){
      std::cout << "there is a warning .." <<std::endl;
      int warnings = (static_cast<int>(bytes[20]));
      switch (warnings) {
      case 0:
        std::cout << "not pgv form matrix code.." <<std::endl;
        break;
      case 1:
        std::cout << "too close to the matrix code.." <<std::endl;
        break;
      case 2:
        std::cout << "too long to the matrix code.." <<std::endl;
        break;
      case 6:
        std::cout << "too blur to find the matrix code.." <<std::endl;
        break;
      case 10:
        std::cout << "beyound the form of the matrix code.." <<std::endl;
        break;
      default:
        break;
      }
    }
  */
    //Byte3_1 == Byte3 and H07
    //X position = Byte3_1 x H80 x H4000 + Byte4 x H4000+ Byte5 x H80 + Byte6
    _positionX = 1e-3 * static_cast<float>((static_cast<unsigned int>(bytes[5]) <<  0) |
                                           (static_cast<unsigned int>(bytes[4]) <<  7) |
                                           (static_cast<unsigned int>(bytes[3]) << 14) |
                                           (static_cast<unsigned int>(bytes[2] & 0x7) << 21));

    _positionY = 1e-3 * static_cast<float>((static_cast<int>(bytes[7]) <<  0) |
                                           (static_cast<int>(bytes[6]) <<  7) );

    _angel = static_cast<float>((static_cast<unsigned int>(bytes[11]) <<  0) |
                                (static_cast<unsigned int>(bytes[10]) <<  7) ) * 1.0;

    if((bytes[1] & 0x40)){
      std::cout << "tag mode.." <<std::endl;
      //Tag number = Byte15 x H80 x H4000 + Byte16 x H4000+ Byte17 x H80 + Byte18
      _tagID = 1e-3 * static_cast<int>((static_cast<unsigned int>(bytes[17]) <<  0) |
                                                   (static_cast<unsigned int>(bytes[16]) <<  7) |
                                                   (static_cast<unsigned int>(bytes[15]) << 14) |
                                                   (static_cast<unsigned int>(bytes[14]) << 21)) * 1;
    }

    //当 CC1 bit 置 ON 时，
    //第一步：Byte15_1 == Byte15 and H07
    //Control code = Byte15_1 x H80 + Byte16
    float conrolCode = 0;
    if((bytes[0] & 0x8)){
        conrolCode = static_cast<float>((static_cast<unsigned int>(bytes[15]) <<  0) |
                                              (static_cast<unsigned int>(bytes[14] & 0x7) <<  7) ) * 1.0;
    }

    std::cout << "positionX :" << _positionX << "   positionY :" << _positionY << "   Angel :" << _angel <<"   tagID :" << _tagID << std::endl;


    QString st = QString("%1|%2|%3|%4)").arg(_positionX).arg(_positionY).arg(_angel).arg(_tagID);
    return st;

}
