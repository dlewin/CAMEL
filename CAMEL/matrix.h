#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QFile>

class Matrix
{
public:
    Matrix(QString Name="Matrix Name",const quint16 Cols=8 ,const quint16 Rows=8, const quint16 Colors=3);
    bool SaveToFile(const QFile FileName);
    bool LoadFromFile(const QFile FileName);
    ~Matrix();
};

#endif // MATRIX_H
