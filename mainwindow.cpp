
#include <QActionGroup>
#include <QtDebug>
#include <QLabel>
#include <QMessageBox>

#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "portsettings.h"

#include "defines.h"
#include "serial.h"
#include "serialconsole.h"
#include "serialutils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("XKHyperCom %1").arg(VERSION_FULL_STR));   // Set the title of the window

    loadSettings();

    loadPorts();

    m_portDialog = new PortSettingsDialog(this);
    m_portDialog->setBaudRate(SerialUtils::baudRateToString(m_settings.BaudRate));
    m_portDialog->setParity(SerialUtils::parityToString(m_settings.Parity));
    m_portDialog->setDataBits(SerialUtils::dataBitsToString(m_settings.DataBits));
    m_portDialog->setStopBits(SerialUtils::stopBitsToString(m_settings.StopBits));

    m_serial = new SerialThread(this);
    connect(m_serial, SIGNAL(readData(QByteArray )), this, SLOT(readSerialData(QByteArray )));
    connect(m_serial, SIGNAL(readEscapeSequence(int )), this, SLOT(readSerialEscape(int )));
    connect(m_serial, SIGNAL(serialStatus(QString)), this, SLOT(serialStatus(QString)));
    connect(m_serial, SIGNAL(serialError(QString)), this, SLOT(serialError(QString)));

    m_statusLabel = new QLabel(tr("Loading %1").arg(m_port));
    statusBar()->addWidget(m_statusLabel);

    m_serial->open(m_port, m_settings);

    m_serial->start();

    m_serialConsole = new SerialConsole(this);
    connect(m_serialConsole, SIGNAL(textInserted(QString )), this, SLOT(serialTextInserted(QString)));

    ui->centralwidget->layout()->addWidget(m_serialConsole);
}

MainWindow::~MainWindow()
{
    saveSettings();

    m_serial->exit();

    m_serial->wait();

    delete m_portDialog;
    delete m_serial;
    delete ui;
}

void MainWindow::loadPorts()
{
    ui->menuFile->clear();

    m_ports = new QActionGroup(this);
    m_ports->setExclusive(true);

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i = 0; i < ports.size(); i++) {
        QString fullName;
        QString friendName = ports.at(i).friendName;
        QString name = ports.at(i).portName;
        if (name.contains("LPT")) {
            continue;
        }

#ifdef Q_WS_WIN
        name.remove("\\\\.\\");
        fullName = QString("%1").arg(friendName);
#else

#ifdef Q_WS_X11
        name.prepend("/dev/");
#endif
        fullName = QString("%1 (%2)").arg(friendName)
                                     .arg(name);
#endif

        QAction * com = new QAction(fullName, this);
        com->setToolTip(name);
        com->setCheckable(true);

        if (com->toolTip() == m_port) {
            com->setChecked(true);
        }

        m_ports->addAction(com);
    }

    connect(m_ports, SIGNAL(triggered(QAction*)),
            this, SLOT(portActionSelected(QAction*)));

    ui->menuFile->addActions(m_ports->actions());
    ui->menuFile->addSeparator();
    ui->menuFile->addAction(ui->actionRefreshDevices);
    ui->menuFile->addAction(ui->actionPortOptions);
    ui->menuFile->addSeparator();
    ui->menuFile->addAction(ui->actionQuit);
}

void MainWindow::loadSettings()
{
    QSettings settings;

    m_port = settings.value(PORT_SETTINGS_PREFIX + "Port", "/dev/ttyS0").toString();

    m_settings.BaudRate = SerialUtils::stringToBaudRate(settings.value(PORT_SETTINGS_PREFIX + "BaudRate",
                                                                       SerialUtils::baudRateToString(BAUD115200)).toString());
    m_settings.Parity   = SerialUtils::stringToParity(settings.value(PORT_SETTINGS_PREFIX + "Parity",
                                                                     SerialUtils::parityToString(PAR_NONE)).toString());
    m_settings.DataBits = SerialUtils::stringToDataBits(settings.value(PORT_SETTINGS_PREFIX + "DataBits",
                                                                       SerialUtils::dataBitsToString(DATA_8)).toString());
    m_settings.StopBits = SerialUtils::stringToStopBits(settings.value(PORT_SETTINGS_PREFIX + "StopBits",
                                                                       SerialUtils::stopBitsToString(STOP_2)).toString());
    m_settings.FlowControl = FLOW_OFF;
    m_settings.Timeout_Millisec = 10;
}

void MainWindow::saveSettings()
{
    QSettings settings;

    settings.setValue(PORT_SETTINGS_PREFIX + "Port", m_port);
    settings.setValue(PORT_SETTINGS_PREFIX + "BaudRate", SerialUtils::baudRateToString(m_settings.BaudRate));
    settings.setValue(PORT_SETTINGS_PREFIX + "Parity", SerialUtils::parityToString(m_settings.Parity));
    settings.setValue(PORT_SETTINGS_PREFIX + "DataBits", SerialUtils::dataBitsToString(m_settings.DataBits));
    settings.setValue(PORT_SETTINGS_PREFIX + "StopBits", SerialUtils::stopBitsToString(m_settings.StopBits));
}

void MainWindow::readSerialData(QByteArray data)
{
    m_serialConsole->insertTermData(data);
}

void MainWindow::readSerialEscape(int sequence)
{
    if (sequence == ESCAPE_SEQUENCE_BACKSPACE) {
        m_serialConsole->textCursor().deletePreviousChar();
    }
}

void MainWindow::serialTextInserted(QString text)
{
    m_serial->write(text.toLatin1());
}

void MainWindow::serialStatus(QString status)
{
    m_statusLabel->setText(status);
    m_statusLabel->setStyleSheet("QLabel { color : black; }");
}

void MainWindow::serialError(QString error)
{
    m_statusLabel->setText(error);
    m_statusLabel->setStyleSheet("QLabel { color : red; }");
}

void MainWindow::portActionSelected(QAction * action)
{
    m_port = action->toolTip();

    if (m_serial->isOpen()) {
        m_serial->close();
    }

    if (!m_serial->isOpen()) {
        m_serial->open(m_port, m_settings);
    }
}


void MainWindow::on_actionPortOptions_triggered(bool )
{
    if (m_portDialog->exec() == QDialog::Accepted) {
        m_serial->close();

        m_settings.BaudRate = SerialUtils::stringToBaudRate(m_portDialog->baudRate());
        m_settings.Parity = SerialUtils::stringToParity(m_portDialog->parity());
        m_settings.DataBits = SerialUtils::stringToDataBits(m_portDialog->dataBits());
        m_settings.StopBits = SerialUtils::stringToStopBits(m_portDialog->stopBits());

        m_serial->open(m_port, m_settings);

        saveSettings();
    }
}

void MainWindow::on_actionAbout_triggered(bool )
{
    QString qextProjectUrl = "http://qextserialport.sourceforge.net/";
    QString about = QString("<b>XKHyperCom %1</b><br/>").arg(VERSION_FULL_STR);

    about += "<br/>XKHyperCom is a Qt4 Gui application to communicate<br/>";
    about += "via the serial port on Unix and Windows platforms.<br/>";

    about += "<br/>Special thanks to the <a href=\"" + qextProjectUrl + "\">QextSerialPort</a> project<br/>";
    about += "for their cross-platform serial port libraries.<br/>";

    about += "<br/>Author:<br/>";
    about += "&nbsp;&nbsp;Jesse L. Zamora<br/>";
    about += "&nbsp;&nbsp;xtremekforever@gmail.com<br/>";

    about += "<br/>Copyright (C) 2011 AlarmasABC<br/>";
    QMessageBox::about(this, "About XKHyperCom", about);
}

void MainWindow::on_actionAboutQt_triggered(bool)
{
    QMessageBox::aboutQt(this, "About Qt");
}

