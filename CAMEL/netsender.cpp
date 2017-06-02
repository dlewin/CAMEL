#include "netsender.h"

NetSender::NetSender(QObject *parent) : QObject(parent)
{
 MainSocket = new QTcpSocket(this)  ;
}

uint NetSender::CreateConnection(QString address, quint16 port)
{
    MainSocket->connectToHost(address,port);
    return  0 ;
}

uint NetSender::SendData(QVector<QRgb> &PaternVect)
{
    if ( MainSocket->waitForConnected() )
    {
        QString DataToSend ;
        qDebug() << "Connected to Server" ;
        foreach (QString QSValue, PaternVect)
        {
            ICI
        }
    }

    return  0 ;
}
