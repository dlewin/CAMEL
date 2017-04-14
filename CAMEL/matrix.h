#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QFile>

class Matrix
{
public:
    Matrix(const QString MName="Matrix Name",const quint16 MCols=8 ,const quint16 MRows=8, const quint16 MColors=3);
    const QString Name;
    const quint16 Cols  ;
    const quint16 Rows  ;
    const quint16 Colors ;
    bool SaveToFile(const QString InifileName );
    ~Matrix();
    bool LoadFromFile(QString InifileName);
};

#endif // MATRIX_H
