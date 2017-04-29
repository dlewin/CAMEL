#include "projectmatrix.h"

#define MAGIC_NUMBER            0xDEADFACE
#define BIN_FILE_VERSION        1
#define ERR_BAD_FILE_FORMAT     -1
#define ERR_BAD_FILE_TOO_OLD    -2
#define ERR_BAD_FILE_TOO_NEW    -3
#define ERR_MTX_FMT_UNKNOWN     -4

#define EMPTY_SEQUENCE          -11

///TODO : For the network sender = the code is in MyButtonGroup.Send
ProjectMatrix::ProjectMatrix(const QString M_Name, const quint16 M_Cols, const quint16 M_Rows, const quint32 M_ColorsDepth, QWidget *centralWidget)
{
    MathMatrix ProjMatrix(M_Name,M_Cols,M_Rows,M_ColorsDepth);
    Cols=M_Cols;
    Rows=M_Rows;
    ColorDepth=M_ColorsDepth;

    QVector<QVector<QRgb>> Proj_VectorMatrix(1);
    ProjMatrix.SetLine(1,0xFF123456) ;
    AppendPattern(ProjMatrix, Proj_VectorMatrix );          // Copy the current Pattern Matrix into the current project Vector of patterns
    TestReadVector(Proj_VectorMatrix) ;

    ConfigurationManager ConfMgr ;
    QString MatxDims = QString::number(Rows) +"x" +QString::number(Cols) +"@" +QString::number(ColorDepth) ;
    ConfMgr.SaveToFile("Camel.ini", MatxDims) ;

    GuiMatrix Matrix_8x8x3(Cols,Rows,ColorDepth,centralWidget);

}

void ProjectMatrix::RemoveAllPatterns(QVector<QVector<QRgb> > &MatrixVector)
{
    MatrixVector.clear();
}

int ProjectMatrix::RemoveLastPattern(QVector<QVector<QRgb> > &MatrixVector)
{
    if (MatrixVector.isEmpty() )
        return EMPTY_SEQUENCE ;

    MatrixVector.removeLast();
    return 0 ;
}

 /// TODO : Retrieve LoadPattern return that will be sent to Gui_Matrix with an Error management
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
    return 0 ;
}

// Read the current pattern defined in the working matrix and append it the sequence
void ProjectMatrix::AppendPattern(MathMatrix ImgToRead, QVector<QVector<QRgb>> &MatrixVector)
{
    ImgToRead.CopyPatternToSequence( MatrixVector );
}



// Save all the patterns in the 2D Vector into the Sequence binary file

int ProjectMatrix::SavePattern(QString Filename, QVector<QVector<QRgb>> &MatrixVector)
{
    if (MatrixVector.isEmpty() )
        return EMPTY_SEQUENCE ;

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
    return 0;
}


void ProjectMatrix::TestReadVector( QVector<QVector<QRgb> > &MatrixVector)
{
    if (MatrixVector.isEmpty() )
        qDebug() << "Vector is Empty" ;
    for ( int indRow = 0; indRow < MatrixVector.size()  ; ++indRow )
        for ( int indCol = 0; indCol <MatrixVector[indRow].size() ; ++indCol )
        {
            qDebug() << MatrixVector[indRow][indCol] ;
        }
}
