#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qextserialport.h>

#define PORT_SETTINGS_PREFIX    QString("/PortSettings/")


namespace Ui {
    class MainWindow;
}

class PortSettingsDialog;
class QLabel;
class QActionGroup;
class SerialThread;
class SerialConsole;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadPorts();

    void loadSettings();
    void saveSettings();

public slots:
    void readSerialData(QByteArray data);
    void readSerialEscape(int sequence);

    void serialTextInserted(QString text);

    void serialStatus(QString status);
    void serialError(QString error);

private slots:
    void portActionSelected(QAction * action);

    void on_actionPortOptions_triggered(bool );

    void on_actionAbout_triggered(bool );
    void on_actionAboutQt_triggered(bool );

private:
    Ui::MainWindow *ui;

    QLabel * m_statusLabel;

    SerialThread * m_serial;

    SerialConsole * m_serialConsole;

    QString m_port;
    QActionGroup * m_ports;

    PortSettings m_settings;

    PortSettingsDialog * m_portDialog;
};

#endif // MAINWINDOW_H
