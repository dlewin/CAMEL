#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QFile>
#include <QImage>

class MathMatrix
{
private:
    const QString Name ;
    const quint16 Cols ;
    const quint16 Rows ;
    const quint32 Colors ;
    QImage WorkMatrix;
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
    void SetLine(int Line, quint32 Color);
    void SetColumn(int Column, quint32 Color);
    void SetBorder(quint32 Color); /// NOTE : Improve it with a <Depth> paramater
    void ColShift(int Offset);
    void LineShift(int Offset);
    void Rotate(int Angle) ;
    void Invert() ;
};

#endif // MATRIX_H
