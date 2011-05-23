#include "serial.h"

#include <QtDebug>
#include <QSocketNotifier>

#include <qextserialport.h>

SerialThread::SerialThread(QObject * parent) :
    QThread(parent)
{
    m_port = new QextSerialPort();
    connect(m_port, SIGNAL(readyRead()), this, SLOT(read()));
    connect(m_port, SIGNAL(dsrChanged(bool)), this, SLOT(statusChanged(bool)));

}

SerialThread::~SerialThread()
{
    if (m_port->isOpen()) {
        m_port->close();
    }
}

void SerialThread::run()
{
    exec();
}

void SerialThread::open(QString & tty, PortSettings & settings)
{
    if (m_port->isOpen()) return;

    m_port->setPortName(tty);
    if (m_port->open(QIODevice::ReadWrite)) {
        m_port->setBaudRate(settings.BaudRate);
        m_port->setFlowControl(settings.FlowControl);
        m_port->setParity(settings.Parity);
        m_port->setDataBits(settings.DataBits);
        m_port->setStopBits(settings.StopBits);
        m_port->setTimeout(settings.Timeout_Millisec);
        m_port->setRts(true);
        m_port->setDtr(true);

        serialStatus(QString("%1 is open").arg(tty));
    } else {
        serialError(QString("Error opening %1").arg(tty));

        qDebug("Error opening port!\n");
    }
}

void SerialThread::close()
{
    if (m_port->isOpen()) {
        m_port->flush();
        m_port->close();
    }
}

void SerialThread::statusChanged(bool status)
{
    if (status)
        qDebug() << "DTR 1";
    else
        qDebug() << "DTR 0";
}


bool SerialThread::isOpen()
{
    return m_port->isOpen();
}


void SerialThread::read()
{
    if (!m_port->isOpen()) {
        return;
    }

    char data[SERIAL_BUFSIZE];

    int bytes_read = 0;
    bytes_read = m_port->read(data, SERIAL_BUFSIZE);

    if (bytes_read < 0) {
        serialError(QString("Error reading from %1").arg(m_port->portName()));
        qDebug() << "Error Code: " << bytes_read;
        return;
    }

    for (int i = 0; i < bytes_read; i++) {
        int c = data[i];

        m_inBuf.append(c);

    }

    if (m_inBuf.size() > 0) {
        readData(m_inBuf);
        m_inBuf.clear();
    }
}

void SerialThread::write(QByteArray data)
{
    m_port->write(data, data.size());
}
