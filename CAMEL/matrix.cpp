#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

MathMatrix::MathMatrix(const QString MName, const quint16 MCols, const quint16 MRows, const quint32 MColors):
    Name(MName),Cols(MCols),Rows(MRows),Colors( MColors)
{
     WorkMatrix = new QImage(Cols,Rows,QImage::Format_RGB32);
     Name = MName;
     Cols= MCols ;
     Rows = MRows;
     Colors  = MColors;
     Reset();
}

MathMatrix::~MathMatrix()
{        
}

void MathMatrix::Fill(uint Value)
{
    WorkMatrix->fill(Value);
}

// Clear the whole Matrix with 0
void MathMatrix::Reset()
{
    Fill(0) ;
}

void MathMatrix::SetPoint(int Col, int Row, quint32 Color)
{
    WorkMatrix->setPixel( Col, Row, Color );
}

void MathMatrix::SetLine(uint Line,quint32 Color)
{
    for ( int i=0;i<WorkMatrix->width();++i )
         SetPoint(Line,i,Color);
}

void MathMatrix::SetColumn(uint Column,quint32 Color)
{
    for (int i=0; WorkMatrix->height();++i )
        SetPoint(i,Column,Color) ;
}

void MathMatrix::SetBorder(quint32 Color)
{
    SetLine( 0, Color) ;
    SetLine( WorkMatrix->height()-1 , Color) ;
    SetColumn(0, Color) ;
    SetColumn( WorkMatrix->width()-1,Color) ;
}

QImage  MathMatrix::ColShift(int Offset)
{
   return( WorkMatrix->transformed(QTransform().translate(Offset,0)) );
}

QImage  MathMatrix::LineShift(int Offset)
{
    return(  WorkMatrix->transformed(QTransform().translate(0,Offset)) );
}

QImage  MathMatrix::Rotate(int Angle)
{
    return(  WorkMatrix->transformed(QTransform().rotate(Angle)) );
}

void MathMatrix::Invert()
{
   WorkMatrix->invertPixels();
}

void MathMatrix::TestMatrix()
{
    qDebug() << "TestMatrix : " << WorkMatrix->width() << " - " << WorkMatrix->height();
    for(int i=0; i< WorkMatrix->width();++i )
        for (int j=0; j< WorkMatrix->height();++j )
        {
            qDebug() <<  QString::number( WorkMatrix->pixel(i,j), 16 );
        }
}

