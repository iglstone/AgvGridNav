#ifndef PGV100_H
#define PGV100_H

//#include "Rs485.h"
#include "serial485.h"

class PGV100
{
public:
    PGV100(Serial485 &bus, const unsigned int id);
    QString grab(void);

private:
    float positionX(void) const { return _positionX; }
    float positionY(void) const { return _positionY; }
    float angel(void) const { return _angel; }
    int   tagID(void) const { return _tagID; }

    Serial485 & _bus;
    unsigned int _id;

    float _positionX;
    float _positionY;
    float _angel;
    int _tagID;
};

#endif // PGV100_H
