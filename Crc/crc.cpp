#include "crc.h"

CrcTools::CrcTools(QObject *parent) : QObject(parent)
{


}

unsigned short CrcTools::CRC16(unsigned char *dat, unsigned int len)
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


