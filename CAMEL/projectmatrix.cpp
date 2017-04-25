#include "projectmatrix.h"

ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_Colors)
{
    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_Colors);
    ProjMatrix.SetLine(1,0xFF000001) ;
    ProjMatrix.LineShift( 1);
    ReadMatrix(ProjMatrix );
   // ProjMatrix.TestMatrix();

    SequenceManager Sequencer();
}


void ProjectMatrix::ReadMatrix(MathMatrix ImgToRead)
{
    QVector<QRgb> MatrixToRead;
    ImgToRead.GetTableVector( MatrixToRead );

    for (auto it: MatrixToRead )
        qDebug() <<  QString::number( it , 16 ) ;
}
