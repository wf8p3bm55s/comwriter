#include <QCoreApplication>
#include <QQueue>
#include <QTextStream>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream standardError(stderr);

    if (argc != 5) {
        standardError <<
                      a.tr("Number of arguments not equal 4.");
        return 1;
    }

    QQueue<int> data;

    for (int i = 1; i < 5; i++) {
        bool ok;
        data.enqueue(QString(argv[i]).toInt(&ok));

        if (!ok) {
            standardError <<
                          a.tr("Can't parse arguments.");
            return 1;
        }
    }

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    if (ports.isEmpty()) {
        standardError <<
                      a.tr("Can't find any serial port.");
        return 1;
    }

    qDebug() << "Arguments:";

    for (const auto &number : data) {
        qDebug() << number;
    }

    qDebug() << "Ports:";

    for (const auto &port : ports) {
        qDebug() << port.portName();
    }

    return a.exec();
}
