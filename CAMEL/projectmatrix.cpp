#include "projectmatrix.h"

ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth)
{


    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_ColorsDepth);
    ProjMatrix.SetLine(1,0xFF000001) ;
    ProjMatrix.LineShift( 1);
    ReadMatrix(ProjMatrix );

    SequenceManager Sequencer();
    ConfigurationManager ConfMgr;
    ConfMgr.SaveToFile("Sequencefile.ini", M_Name,  M_Cols,  M_Rows,  M_ColorsDepth);
    SavePattern("Pattern1.bin") ;
}



void ProjectMatrix::ReadMatrix(MathMatrix ImgToRead)
{
    ImgToRead.GetImageVector( MatrixToRead );
}

///TODO for ConfigurationManager::SaveToFile => in a binary format:
/// 1) read a pattern via ReadMatrix
/// 2) write it to a single sequence file
/// 3) repeat for each patterns in the sequence

// Save the Current defined matrix as a pattern in a binary file

void ProjectMatrix::SavePattern(QString Filename)
{
    static quint16 CurrentPattern_Counter {0} ;

    QFile fileout(Filename);
    if (fileout.open( QFile::WriteOnly ))
    {
        QDataStream out(&fileout);
        // Header
        out << (quint32)0xDEADFACE;  // Magic Number
        out << (quint16) CurrentPattern_Counter;

        for (auto iter : MatrixToRead)
        {
            out << iter;
        }
        fileout.close();

        CurrentPattern_Counter++ ;
    }
}
