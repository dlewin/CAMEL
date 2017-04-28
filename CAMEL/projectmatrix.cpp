#include "projectmatrix.h"

#define MAGIC_NUMBER            0xDEADFACE
#define BIN_FILE_VERSION        1
#define ERR_BAD_FILE_FORMAT     -1
#define ERR_BAD_FILE_TOO_OLD    -2
#define ERR_BAD_FILE_TOO_NEW    -3
#define ERR_MTX_FMT_UNKNOWN     -4

ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth)       
{
    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_ColorsDepth);
    Cols=M_Cols;
    Rows=M_Rows;
    ColorDepth=M_ColorsDepth;

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

    MatrixToRead.clear();
    int ret = LoadPattern("Pattern3.bin", MatrixToRead) ;
    if (ret<0)
        qDebug() << "!! LoadPattern Error : " << ret ;          /// TODO : will be sent to Gui_Matrix with an Error management

}


int ProjectMatrix::LoadPattern(QString Filename, QVector<QVector<QRgb> > &MatrixVector)
{
    QFile filein(Filename);
    if (!filein.open(QIODevice::ReadOnly))
            return -1;

    QDataStream in(&filein);

    // Read and check the header
    quint32 magic;
    in >> magic;
    if (magic != MAGIC_NUMBER)
        return ERR_BAD_FILE_FORMAT;

    // Read the version
    quint16 version;
    in >> version;
    if (version < BIN_FILE_VERSION)
        return ERR_BAD_FILE_TOO_OLD;
    if (version > BIN_FILE_VERSION)
        return ERR_BAD_FILE_TOO_NEW;

    // Retrieve the sequence size ( how much patterns)
    quint32 SeqSize ;
    in >> SeqSize ;

    //    MatrixFormat
    quint16 SeqFileRows, SeqFileCols ;
    quint32 SeqFileColors ;
    in >> SeqFileRows;
    in >> SeqFileCols;
    in >> SeqFileColors;

    // Check the dims of the matrix in the seq file
    if ( SeqFileRows!=8 && SeqFileCols!=8 && SeqFileColors!=3 )
        return ERR_MTX_FMT_UNKNOWN ;                                ///WARNING Matrix other than 8x8@3 are not handled

    QVector<QVector<QRgb> > Temp_MatrixVector;
    QRgb RGBValue = 0 ;

    for(uint i = 0; i < SeqSize; ++i)
    {
        for(uint indRow = 0;indRow < SeqFileRows; ++indRow )
        {
            for(uint indCol = 0;indCol < SeqFileCols ;++indCol)
            {
                QVector<QRgb> inner_vector;
                in >> RGBValue;

                inner_vector.push_back(RGBValue);
                Temp_MatrixVector.push_back(inner_vector);
            }
        }
    }

    MatrixVector = Temp_MatrixVector ;                      // now everything is ok : copy the  temp vector to the current working one

//    for ( int indRow = 0; indRow < Temp_MatrixVector.size()  ; ++indRow )
//        for ( int indCol = 0; indCol <Temp_MatrixVector[indRow].size() ; ++indCol )
//        {
//        qDebug() << Temp_MatrixVector[indRow][indCol] ;
//        }

    return 0 ;
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
        out << (quint32) MAGIC_NUMBER ;             // Magic Number
        out << (quint16) BIN_FILE_VERSION;
        out << (quint16) MatrixVector.size() - 1;  // Tells how much patterns this sequence file have
        out << (quint16) Rows;
        out << (quint16) Cols;
        out << (quint32) ColorDepth;


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
