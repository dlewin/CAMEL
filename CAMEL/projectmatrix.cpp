#include "projectmatrix.h"

ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth)       
{


    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_ColorsDepth);
    QVector<QVector<QRgb>> MatrixToRead(1);

    ProjMatrix.SetLine(1,0xFF000001) ;
    ProjMatrix.LineShift( 1);

    ReadMatrix(ProjMatrix, MatrixToRead );

    ProjMatrix.SetLine(0,0xFF123456) ;
    ReadMatrix(ProjMatrix, MatrixToRead );

    SequenceManager Sequencer();
    ConfigurationManager ConfMgr;
    ConfMgr.SaveToFile("Sequencefile.ini", M_Name,  M_Cols,  M_Rows,  M_ColorsDepth);
    SavePattern("Pattern3.bin", MatrixToRead) ;
}


void ProjectMatrix::ReadMatrix(MathMatrix ImgToRead, QVector<QVector<QRgb>> &MatrixVector)
{
    static quint16 CurrentVector_Index =0;

    ImgToRead.CopyPatternToSequence( MatrixVector,CurrentVector_Index++  );
}

// Save the Current defined matrix as a pattern in a binary file

void ProjectMatrix::SavePattern(QString Filename, QVector<QVector<QRgb>> &MatrixVector)
{
    QFile fileout(Filename);
    if (fileout.open( QFile::WriteOnly ))
    {
        QDataStream out(&fileout);
        // Header
        out << (quint32)0xDEADFACE;  // Magic Number
        out << (quint16) MatrixVector.size() - 1;  // Tells how much patterns this sequence file have

        // now save the Patterns Data from the 2D Vector
        for(int i = 0;i < MatrixVector.size();++i)
        {
              for(int j = 0;j < MatrixVector[i].size();++j)
              {
                 out <<  MatrixVector[i][j] ;
              }
        }
        fileout.close();
    }
}
