#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QFile>

class MathMatrix
{
private:
    const QString Name ;
    const quint16 Cols ;
    const quint16 Rows ;
    const quint16 Colors ;
public:
    MathMatrix(const QString MName="Matrix Name",const quint16 MCols=8 ,const quint16 MRows=8, const quint16 MColors=3);
    ~MathMatrix();
    QString getName(){return Name;}
    quint16 getCols;
    quint16 setCols;
    quint16 getRows;
    quint16 setRows;
    quint16 getColors ;
    quint16 setColors ;



};

#endif // MATRIX_H
