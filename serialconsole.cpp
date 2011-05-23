
#include <stdio.h>

#include <QtDebug>
#include <QKeyEvent>

#include "serialconsole.h"

SerialConsole::SerialConsole(QWidget *parent) :
    QPlainTextEdit(parent)
{
    this->setReadOnly(true);

    m_readEscape = false;
    m_asciiEscape = false;
}

void SerialConsole::insertTermData(QByteArray data)
{
    for (int i = 0; i < data.size(); i++) {
       int c = (int)data[i];

        /*if (c == 27) {
            m_readEscape = true;
        } else {
            if (m_readEscape && c == '[') {
                m_asciiEscape = true;
            } else if (m_asciiEscape) {
                if (i + 1 < data.size()) {
                    if (data[i + 1] == ';') {
                        continue;
                    }
                }

                switch (c) {
                case 'J':
                    this->textCursor().deletePreviousChar();
                    break;
                default:
                    qDebug() << "Unknown Escape:" << c;
                    break;
                }

                m_readEscape = false;
                m_asciiEscape = false;
            } else {*/
                if (isprint(c) || c == '\n' || c == '\t') {
                    QString str;
                    str.append(c);

                    this->insertPlainText(str);
                    this->centerCursor();
                }
            /*}
        }*/
    }
}


void SerialConsole::keyPressEvent(QKeyEvent *event)
{
    if (event->text().size() > 0) {
        qDebug() << "Key Press:" << (int)event->text().at(0).toLatin1();
        textInserted(event->text());
    }
}
