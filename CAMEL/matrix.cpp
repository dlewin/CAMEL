#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

MathMatrix::MathMatrix(const QString MName, const quint16 MCols, const quint16 MRows, const quint32 MColors):
    Name(MName),Cols(MCols),Rows(MRows),Colors( MColors)
{
     //QImage* WorkMatrix = new QImage(Cols,Rows,QImage::Format_RGB32);
}

MathMatrix::~MathMatrix()
{        
}

void MathMatrix::Fill(uint Value)
{
    WorkMatrix.fill(Value);
}

// Clear the whole Matrix with 0
void MathMatrix::Reset()
{
    Fill(0) ;
}

void MathMatrix::SetPoint(int Col, int Row, quint32 Color)
{
    WorkMatrix.setPixel( Col, Row, Color );
}

void MathMatrix::SetLine(int Line,quint32 Color)
{
    for ( int i=0;i<WorkMatrix.width();++i )
         SetPoint(0,i,Color);
    /// TODO: change to apply for all lines
}

void MathMatrix::SetColumn(int Column,quint32 Color)
{
    for (int i=0; WorkMatrix.height();++i )
        SetPoint(i,0,Color) ;
    /// TODO: change to apply for all cols
}

void MathMatrix::SetBorder(quint32 Color)
{
    SetLine( 0, Color) ;
    SetLine( WorkMatrix.height()-1 , Color) ;
    SetColumn(0, Color) ;
    SetColumn( WorkMatrix.width()-1,Color) ;
}

void MathMatrix::ColShift(int Offset)
{
    WorkMatrix = WorkMatrix.transformed(QTransform().translate(Offset,0));
}

void MathMatrix::LineShift(int Offset)
{
   WorkMatrix = WorkMatrix.transformed(QTransform().translate(0,Offset));
}

void MathMatrix::Rotate(int Angle)
{
    WorkMatrix = WorkMatrix.transformed(QTransform().rotate(Angle));
}

void MathMatrix::Invert()
{
   WorkMatrix.invertPixels();
}
