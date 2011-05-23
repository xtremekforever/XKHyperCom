#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QThread>

#include <qextserialport.h>

#define ESCAPE_SEQUENCE_BACKSPACE   1

class QSocketNotifier;
class QextSerialPort;

#define SERIAL_BUFSIZE 4096               // The size of one line just about

class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QObject *parent = 0);
    ~SerialThread();

    void run();

    void open(QString & tty, PortSettings & settings);
    void close();

    void write(QByteArray data);

    QString port() { return m_port->portName(); }

    bool isOpen();

signals:
    void readData(QByteArray data);

    void readEscapeSequence(int sequence);

    void serialStatus(QString status);
    void serialError(QString error);

public slots:
    void read();
    void statusChanged(bool);

private:
    QByteArray m_inBuf;

    QByteArray m_outBuf;

    QextSerialPort * m_port;
};

#endif // SERIAL_H
