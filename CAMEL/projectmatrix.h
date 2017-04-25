#ifndef PROJECTMATRIX_H
#define PROJECTMATRIX_H

#include "matrix.h"
#include "configurationmanager.h"
#include "sequencemanager.h"

class ProjectMatrix
{
private:
    MathMatrix ProjMatrix ;
public:
    ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth);
    void ReadMatrix(MathMatrix ImgToRead);
};

#endif // PROJECTMATRIX_H
