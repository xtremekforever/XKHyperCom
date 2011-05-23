#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <QPlainTextEdit>

class QKeyEvent;

class SerialConsole : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SerialConsole(QWidget *parent = 0);

    void insertTermData(QByteArray data);
protected:
    void keyPressEvent(QKeyEvent * event);

signals:
    void textInserted(QString data);

public slots:

private:
    bool m_readEscape;
    bool m_asciiEscape;
    bool m_readEscapeChar;
    int m_escapeChar;
};

#endif // SERIALCONSOLE_H
