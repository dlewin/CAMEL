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
    QVector<QRgb> MatrixToRead;

public:
    ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth);
    void ReadMatrix(MathMatrix ImgToRead);
    void SavePattern(QString Filename);
};

#endif // PROJECTMATRIX_H
