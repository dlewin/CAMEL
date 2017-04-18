#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

MathMatrix::MathMatrix(const QString MName, const quint16 MCols, const quint16 MRows, const quint16 MColors):
    Name(MName),Cols(MCols),Rows(MRows),Colors( MColors)
{
    QImage myMatrix(Cols,Rows,QImage::Format_RGB32); //will create a container of 8 by 8 bits (not bytes).
}



MathMatrix::~MathMatrix()
{

}

/*
    myMatrix.fill(0); to turn everything off.
    Point: myMatrix.setPixel(0,0,1);
    Line(1): for(int i=0;i<myMatrix.width();++i) myMatrix.setPixel(0,i,1);
    Column(1): for(int i=0;i<myMatrix.height();++i) myMatrix.setPixel(i,0,1);
    Border: for(int i=0;i<myMatrix.width();++i) {myMatrix.setPixel(0,i,1); myMatrix.setPixel(myMatrix.height()-1,i,1);} for(int i=0;i<myMatrix.height();++i) {myMatrix.setPixel(i,0,1); myMatrix.setPixel(i,myMatrix.width()-1,1);}
    Column Shift(1): myMatrix=myMatrix.transformed(QTransform().translate(1,0));
    Column Shift(-1): myMatrix=myMatrix.transformed(QTransform().translate(-1,0));
    Line Shift(1): myMatrix=myMatrix.transformed(QTransform().translate(0,1));
    Line Shift(-1): myMatrix=myMatrix.transformed(QTransform().translate(0,-1));
    Rotate(1): myMatrix=myMatrix.transformed(QTransform().rotate(270));
    Rotate(-1): myMatrix=myMatrix.transformed(QTransform().rotate(90));
    Invert: myMatrix.invertPixels();
*/
