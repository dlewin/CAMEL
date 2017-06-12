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

uint NetSender::SendData(QVector<uint> &PaternVect)
{
    if ( MainSocket->waitForConnected() )
    {
        QString DataToSend ;
        qDebug() << "Connected to Server" ;
   //     foreach (QString QSValue, PaternVect)
        {
            ///TODO ICI
        }
    }

    return  0 ;
}

NetSender::~NetSender()
{
    MainSocket->close();
}
