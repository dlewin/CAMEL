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

uint NetSender::SendData(QString DataToSend)
{
    if ( MainSocket->waitForConnected() )
    {
        qDebug() << "Connected to Server" ;

    }

    return  0 ;
}
