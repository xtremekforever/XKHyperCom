#include "serialutils.h"

SerialUtils::SerialUtils()
{
}

QString SerialUtils::baudRateToString(BaudRateType baud)
{
    switch (baud) {
    case BAUD50:
        return "50";
    case BAUD110:
        return "110";
    case BAUD300:
        return "300";
    case BAUD600:
        return "600";
    case BAUD1200:
        return "1200";
    case BAUD2400:
        return "2400";
    case BAUD4800:
        return "4800";
    case BAUD9600:
        return "9600";
    case BAUD19200:
        return "19200";
    case BAUD38400:
        return "38400";
    case BAUD57600:
        return "57600";
    case BAUD115200:
    default:
        return "115200";
    }
}

BaudRateType SerialUtils::stringToBaudRate(QString baud)
{
    if (baud == "50") {
        return BAUD50;
    } else if (baud == "110") {
        return BAUD110;
    } else if (baud == "300") {
        return BAUD300;
    } else if (baud == "600") {
        return BAUD600;
    } else if (baud == "1200") {
        return BAUD1200;
    } else if (baud == "2400") {
        return BAUD2400;
    } else if (baud == "4800") {
        return BAUD4800;
    } else if (baud == "9600") {
        return BAUD9600;
    } else if (baud == "19200") {
        return BAUD19200;
    } else if (baud == "38400") {
        return BAUD38400;
    } else if (baud == "57600") {
        return BAUD57600;
    } else if (baud == "115200") {
        return BAUD115200;
    }

    return BAUD115200;
}

QString SerialUtils::parityToString(ParityType parity)
{
    switch (parity) {
    case PAR_NONE:
        return "None";
    case PAR_ODD:
        return "Odd";
    case PAR_EVEN:
        return "Event";
    case PAR_SPACE:
        return "Space";
    }

    return "None";
}

ParityType SerialUtils::stringToParity(QString parity)
{
    if (parity == "None") {
        return PAR_NONE;
    } else if (parity == "Odd") {
        return PAR_ODD;
    } else if (parity == "Even") {
        return PAR_EVEN;
    } else if (parity == "Space") {
        return PAR_SPACE;
    }

    return PAR_NONE;
}

QString SerialUtils::dataBitsToString(DataBitsType dataBits)
{
    switch (dataBits) {
    case DATA_5:
        return "5";
    case DATA_6:
        return "6";
    case DATA_7:
        return "7";
    case DATA_8:
    default:
        return "8";
    }
}

DataBitsType SerialUtils::stringToDataBits(QString dataBits)
{
    if (dataBits == "5") {
        return DATA_5;
    } else if (dataBits == "6") {
        return DATA_6;
    } else if (dataBits == "7") {
        return DATA_7;
    } else if (dataBits == "8") {
        return DATA_8;
    }

    return DATA_8;
}

QString SerialUtils::stopBitsToString(StopBitsType stopBits)
{
    switch (stopBits) {
    case STOP_1:
        return "1";
    case STOP_2:
    default:
        return "2";
    }
}

StopBitsType SerialUtils::stringToStopBits(QString stopBits)
{
    if (stopBits == "1") {
        return STOP_1;
    } else if (stopBits == "2") {
        return STOP_2;
    }

    return STOP_2;
}

