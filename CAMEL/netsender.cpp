#include "netsender.h"

NetSender::NetSender(QObject *parent) : QObject(parent)
{
 MainSocket = new QTcpSocket(this)  ;
}
