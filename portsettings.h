#ifndef PORTSETTINGS_H
#define PORTSETTINGS_H

#include <QDialog>

#include <qextserialenumerator.h>



class QAbstractButton;

namespace Ui {
    class PortSettingsDialog;
}

class PortSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    PortSettingsDialog(QWidget *parent = 0);
    ~PortSettingsDialog();

    QString baudRate();
    QString parity();
    QString dataBits();
    QString stopBits();

    void setBaudRate(QString baud);
    void setParity(QString parity);
    void setDataBits(QString dataBits);
    void setStopBits(QString stopBits);

private:
    Ui::PortSettingsDialog *ui;

    QList<QString> m_ports;
};

#endif // PORTSETTINGS_H
