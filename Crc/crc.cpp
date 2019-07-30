#include "crc.h"

CrcTools::CrcTools(QObject *parent) : QObject(parent)
{


}

unsigned short CrcTools::crc16(unsigned char *dat, unsigned int len)
{

    unsigned short crc;
    unsigned char da;

    crc = 0xFFFF;
    while(len--!=0)
    {

        da=(unsigned char) (crc/256);
        crc <<= 8;
        crc ^= crc16_table[da^*dat];
        dat++;
    }

    return crc;
}

unsigned char CrcTools::crc(unsigned char *data, unsigned int len)
{
    unsigned short crc;
    while(len--){
        crc += *(data++);
    }
    crc = 0x01 + (~crc);

    return crc;
}


QString CrcTools::to_string(unsigned short data)
{
    return QString::number((unsigned short)data, 16);
}

QString CrcTools::to_string(unsigned char data)
{
    return QString::number((unsigned char)data, 16);
}


