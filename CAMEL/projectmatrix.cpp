#include "projectmatrix.h"

ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth)       
{
    quint16 CurrentVector_Index =0;
    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_ColorsDepth);
    QVector<QVector<QRgb>> MatrixToRead(1);//,QVector<QRgb>(1,5)) ;

    ProjMatrix.SetLine(1,0xFF000001) ;
    ProjMatrix.LineShift( 1);

    //----------------------------------------------------------------
    qDebug() <<"size :" << MatrixToRead.size() << "CurrentVector_Index" << CurrentVector_Index  ;
    ProjMatrix.SavePattern(MatrixToRead, CurrentVector_Index++ );


        for (int i = 0; i < MatrixToRead.size(); i++)
        {
            for (int j = 0; j < MatrixToRead[i].size(); j++)
            {
                qDebug() << MatrixToRead[i][j];
            }
        }

    //----------------------------------------------------------------
    qDebug() <<"size :" << MatrixToRead.size() << "CurrentVector_Index" << CurrentVector_Index  ;;
    ProjMatrix.SavePattern(MatrixToRead, CurrentVector_Index++ );

        for (int i = 0; i < MatrixToRead.size(); i++)
        {
            for (int j = 0; j < MatrixToRead[i].size(); j++)
            {
                qDebug() << MatrixToRead[i][j];
            }
        }
    //----------------------------------------------------------------


    SequenceManager Sequencer();
    ConfigurationManager ConfMgr;
    ConfMgr.SaveToFile("Sequencefile.ini", M_Name,  M_Cols,  M_Rows,  M_ColorsDepth);
    SavePattern("Pattern1.bin") ;
}



void ProjectMatrix::ReadMatrix(MathMatrix ImgToRead, QVector<QVector<QRgb>> MatrixToRead, quint16 CurVector_Index)
{
    //ImgToRead.GetImageVector( MatrixToRead,CurVector_Index++  );
}

///TODO for ConfigurationManager::SaveToFile => in a binary format:
/// 1) read a pattern via ReadMatrix
/// 2) write it to a single sequence file from a vector of vectors
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
        out << (quint16) CurrentPattern_Counter;  // Tells how much patterns this sequence file have

        // Data
///FIXME : Modify the 1D QVector to 2D
///         for (auto iter : MatrixToRead)
///         {
///             out << iter;
///         }
        fileout.close();

        CurrentPattern_Counter++ ;
    }
}
