#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QFile>

class MathMatrix
{
public:
    MathMatrix(const QString MName="Matrix Name",const quint16 MCols=8 ,const quint16 MRows=8, const quint16 MColors=3);
    const QString Name;
    const quint16 Cols  ;
    const quint16 Rows  ;
    const quint16 Colors ;
    ~MathMatrix();

};

#endif // MATRIX_H
