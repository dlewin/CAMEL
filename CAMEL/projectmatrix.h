#ifndef PROJECTMATRIX_H
#define PROJECTMATRIX_H

#include <QFile>

#include "matrix.h"
#include "configurationmanager.h"
#include "sequencemanager.h"

class ProjectMatrix
{
private:
    MathMatrix ProjMatrix ;


public:
    static QVector<QVector<QRgb>> MatrixToRead;
    int CurVector_Index;
    ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth);
    void ReadMatrix(MathMatrix ImgToRead, QVector<QVector<QRgb>> MatrixToRead, quint16 CurVector_Index);
    void SavePattern(QString Filename);
};

#endif // PROJECTMATRIX_H
