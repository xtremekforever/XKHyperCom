#ifndef SERIALUTILS_H
#define SERIALUTILS_H

#include <qextserialport.h>

class SerialUtils
{
public:
    SerialUtils();

    static QString baudRateToString(BaudRateType baud);
    static BaudRateType stringToBaudRate(QString baud);

    static QString parityToString(ParityType parity);
    static ParityType stringToParity(QString parity);

    static QString dataBitsToString(DataBitsType dataBits);
    static DataBitsType stringToDataBits(QString dataBits);

    static QString stopBitsToString(StopBitsType stopBits);
    static StopBitsType stringToStopBits(QString stopBits);
};

#endif // SERIALUTILS_H
