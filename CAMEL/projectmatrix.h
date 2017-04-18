#ifndef PROJECTMATRIX_H
#define PROJECTMATRIX_H

#include "matrix.h"
#include "configurationmanager.h"
#include "sequencemanager.h"

class ProjectMatrix
{
public:
    ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint16 M_Colors);
};

#endif // PROJECTMATRIX_H
