#include <QCoreApplication>
#include <QTextStream>
#include <QSerialPort>
#include <QSerialPortInfo>

void printError(const QString &message)
{
    static QTextStream standardError(stderr);
    standardError << message;
    standardError.flush();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream standardOutput(stdout);

    if (argc != 5) {
        printError(QObject::tr("Number of arguments not equal 4."));
        return 1;
    }

    QByteArray data;

    for (int i = 1; i < 5; i++) {
        bool ok;
        data.append(QString::number(QString(argv[i]).toInt(&ok)));

        if (!ok) {
            printError(QObject::tr("Can't parse arguments."));
            return 1;
        }
    }

    QList<QSerialPortInfo> portsInfo = QSerialPortInfo::availablePorts();

    if (portsInfo.isEmpty()) {
        printError(QObject::tr("Can't find any serial port."));
        return 1;
    }

    QSerialPort port(portsInfo.first());

    if (!port.setBaudRate(QSerialPort::Baud2400)) {
        printError(QObject::tr("Can't set baud rate. Error code: ") +
                   QString::number(port.error()));
        return 1;
    }

    if (!port.open(QIODevice::WriteOnly)) {
        printError(QObject::tr("Can't open serial port. Error code: ") +
                   QString::number(port.error()));
        return 1;
    }

    if (port.write(data) == -1) {
        printError(QObject::tr("Serial port write error. Error code: ") +
                   QString::number(port.error()));
        port.close();
        return 1;
    }

    port.flush();
    port.close();

    standardOutput << QObject::tr("Succesfuly written.");
    standardOutput.flush();

    return a.exec();
}
