#include "projectmatrix.h"



ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_Colors)
{
    MathMatrix TestMatrix(M_Name,M_Cols,M_Rows,M_Colors);
    qDebug() << TestMatrix.getName();
    TestMatrix.Fill(1);
}
