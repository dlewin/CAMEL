#include "projectmatrix.h"



ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_Colors)
{
    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_Colors);
    ProjMatrix.SetColumn(1,"orange");
    ProjMatrix.TestMatrix();
}
