
#include <QAbstractButton>

#include "portsettings.h"
#include "ui_portsettings.h"

PortSettingsDialog::PortSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSettingsDialog)
{
    ui->setupUi(this);
}

PortSettingsDialog::~PortSettingsDialog()
{
    delete ui;
}


QString PortSettingsDialog::baudRate()
{
    return ui->baudrateComboBox->currentText();
}

QString PortSettingsDialog::parity()
{
    return ui->parityComboBox->currentText();
}

QString PortSettingsDialog::dataBits()
{
    return ui->databitsComboBox->currentText();
}

QString PortSettingsDialog::stopBits()
{
    return ui->stopbitsComboBox->currentText();
}

void PortSettingsDialog::setBaudRate(QString baud)
{
    ui->baudrateComboBox->setCurrentIndex(ui->baudrateComboBox->findText(baud));
}
void PortSettingsDialog::setParity(QString parity)
{
    ui->parityComboBox->setCurrentIndex(ui->parityComboBox->findText(parity));
}
void PortSettingsDialog::setDataBits(QString dataBits)
{
    ui->databitsComboBox->setCurrentIndex(ui->databitsComboBox->findText(dataBits));
}
void PortSettingsDialog::setStopBits(QString stopBits)
{
    ui->stopbitsComboBox->setCurrentIndex(ui->stopbitsComboBox->findText(stopBits));
}

