#ifndef NETSENDER_H
#define NETSENDER_H

#include <QObject>
#include <QTcpSocket>

class NetSender : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* MainSocket ;
public:
    explicit NetSender(QObject *parent = 0);
    uint CreateConnection(QString address, quint16 port) ;
    uint SendData(QVector<QRgb> &PaternVect);

signals:

public slots:
};

#endif // NETSENDER_H
