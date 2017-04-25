#include "projectmatrix.h"

ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth)
{
    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_ColorsDepth);
    ProjMatrix.SetLine(1,0xFF000001) ;
    ProjMatrix.LineShift( 1);
    ReadMatrix(ProjMatrix );
   // ProjMatrix.TestMatrix();

    SequenceManager Sequencer();
    ConfigurationManager ConfMgr;
    bool ConfRet = ConfMgr.SaveToFile("Sequencefile.ini", M_Name,  M_Cols,  M_Rows,  M_ColorsDepth);
}

///TODO for ConfigurationManager::SaveToFile => in a binary format:
/// 1) read a pattern via ReadMatrix
/// 2) write it to a single sequence file
/// 3) repeat for each patterns in the sequence

void ProjectMatrix::ReadMatrix(MathMatrix ImgToRead)
{
    QVector<QRgb> MatrixToRead;
    ImgToRead.GetImageVector( MatrixToRead );

    for (auto it: MatrixToRead )
        qDebug() <<  QString::number( it , 16 ) ;
}
