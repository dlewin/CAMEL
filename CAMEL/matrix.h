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
    QImage *WorkMatrix;

public:
    MathMatrix(const QString MName="Matrix Name", const quint16 MCols=8 , const quint16 MRows=8, const quint32 MColors=3);
    ~MathMatrix();
    QString getName()   { return Name   ;}
    quint16 getCols()   { return Cols   ;}
    quint16 getRows()   { return Rows   ;}
    quint32 getColors() { return Colors ;}

    bool Check_ColRange(int Col) ;
    bool Check_RowRange(int Row) ;
    bool CheckRanges(int Col, int Row);
    bool SetPoint(int Col, int Row, quint32 Color);
    bool SetPoint(int Col, int Row, QColor NamedColor);
    void Fill(uint Value);
    void Fill(QColor NamedColor);
    void Reset();
    bool SetLine(int Line, quint32 Color);
    bool SetLine(int Line, QColor NamedColor);
    bool SetColumn(int Column, quint32 Color);
    bool SetColumn(int Column, QColor NamedColor);
    void SetBorder(quint32 Color); /// NOTE : Improve it with a <Depth> paramater
    void SetBorder( QColor NamedColor );
    QImage ColShift(int Offset);
    QImage LineShift(int Offset);
    QImage Rotate(int Angle) ;
    void Invert() ;
    void TestMatrix();
};

#endif // MATRIX_H
