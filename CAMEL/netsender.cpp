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
    if ( MainSocket->waitForConnected(3000) )
    {
        QString DataToSend ="123COPIUC" ;
        qDebug() << "Connected to Server" ;

   //     foreach (QString QSValue, PaternVect)
        {
            ///TODO ICI
            MainSocket->write( DataToSend.toLatin1() ) ;
            MainSocket->waitForBytesWritten(1000);

//            MainSocket->waitForReadyRead(3000);
//            qDebug() << "Reading: " << MainSocket->bytesAvailable();

//            qDebug() << MainSocket->readAll();

        }
        return 0 ;
    }
    else
    {
        qDebug() << "NOT Connected to Server" ;
        return  1 ;
    }
}

NetSender::~NetSender()
{
    MainSocket->close();
}
