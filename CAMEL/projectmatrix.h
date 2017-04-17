#ifndef PROJECTMATRIX_H
#define PROJECTMATRIX_H

#include "matrix.h"
#include "configurationmanager.h"
#include "sequencemanager.h"
#include "pattern.h"

class ProjectMatrix:MathMatrix
{
public:
    ProjectMatrix(const QString ,const quint16 ,const quint16 , const quint16 );
};

#endif // PROJECTMATRIX_H
