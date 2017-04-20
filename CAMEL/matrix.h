#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QFile>
#include <QImage>

class MathMatrix
{
private:
    QString Name ;
    quint16 Cols;
    quint16 Rows ;
    quint32 Colors ;
    QImage *WorkMatrix; //(quint16,quint16,quint32 );

public:
    MathMatrix(const QString MName="Matrix Name", const quint16 MCols=8 , const quint16 MRows=8, const quint32 MColors=3);
    ~MathMatrix();
    QString getName()   { return Name   ;}
    quint16 getCols()   { return Cols   ;}
    quint16 getRows()   { return Rows   ;}
    quint32 getColors() { return Colors ;}

    void Fill(uint Value);
    void Reset();
    void SetPoint(int Col, int Row, quint32 Color);
    void SetLine(uint Line, quint32 Color);
    void SetColumn(uint Column, quint32 Color);
    void SetBorder(quint32 Color); /// NOTE : Improve it with a <Depth> paramater
    QImage ColShift(int Offset);
    QImage LineShift(int Offset);
    QImage Rotate(int Angle) ;
    void Invert() ;
    void TestMatrix();
};

#endif // MATRIX_H
