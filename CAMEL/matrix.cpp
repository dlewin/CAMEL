#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

//quint16 MathMatrix::CurrentVector_Index=1 ;

MathMatrix::MathMatrix(const QString MName, const quint16 MCols, const quint16 MRows, const quint32 MColors):
    Name(MName),Cols(MCols),Rows(MRows),Colors( MColors)
{
     WorkMatrix = new QImage(Cols,Rows,QImage::Format_RGB32);

     Name = MName;
     Cols= MCols ;
     Rows = MRows;
     Colors  = MColors;
     Reset();
}

MathMatrix::~MathMatrix()
{        
}

// Checks that values are in the Matrix ranges (Col)
bool MathMatrix::Check_ColRange(int Col)
{
    if (( Col <0 ) || ( Col> WorkMatrix->width() ))
        return false;
    else
        return true ;
}

// Checks that values are in the Matrix ranges (Row)
bool MathMatrix::Check_RowRange(int Row)
{
    if ( Row <0 || Row>WorkMatrix->height() )
        return false;
    else
        return true ;
}

// Checks that values are in the Matrix ranges (width and Height)
bool MathMatrix::CheckRanges(int Row, int Col)
{
    if ( Check_ColRange( Row) && Check_RowRange(Col ) )
        return true ;
    else
        return false ;
}

void MathMatrix::Fill(uint Value)
{
    WorkMatrix->fill(Value);
}

void MathMatrix::Fill(QColor NamedColor )
{
    WorkMatrix->fill( NamedColor );
}

void MathMatrix::Reset()
{
    QColor TempColor("transparent");
    Fill( TempColor ) ;
}

bool MathMatrix::SetPoint(int Row, int Col, quint32 Color)
{
    if (! CheckRanges( Row,Col ))
        return false;
    WorkMatrix->setPixel(Row ,Col , Color );

    return true ;
}

bool  MathMatrix::SetPoint(int Row, int Col, QColor NamedColor)
{
   if (! CheckRanges( Col, Row))
       return false;

    QColor TempColor(NamedColor);
    WorkMatrix->setPixelColor( Col, Row, TempColor );

    return true ;
}

QRgb MathMatrix::GetPoint(int Row, int Col)
{    
    if (! CheckRanges( Row, Col))
        return 0x00000000;

    return( WorkMatrix->pixel(Row,Col) );
}

bool MathMatrix::SetLine(int Line,quint32 Color)
{
    if ( !Check_RowRange( Line))
        return false;
    for ( int i=0;i<WorkMatrix->width();++i )
         SetPoint(Line,i,Color);
    return true ;
}

bool MathMatrix::SetLine(int Line,QColor NamedColor)
{
    if ( !Check_RowRange( Line))
        return false;

    QColor TempColor(NamedColor);
    for ( int i=0;i<WorkMatrix->width();++i )
         SetPoint(Line,i,TempColor);
   return true ;
}

bool MathMatrix::SetColumn(int Column,quint32 Color)
{
    if ( !Check_ColRange( Column))
        return false;

    for (int i=0; i< WorkMatrix->height();++i )
        SetPoint(i,Column,Color) ;

    return true ;
}

bool MathMatrix::SetColumn(int Column,QColor NamedColor)
{
    if ( !Check_ColRange( Column))
        return false;

    QColor TempColor(NamedColor);
    for (int i=0; i< WorkMatrix->height();++i )
        SetPoint(i,Column,TempColor) ;

    return true ;
}

void MathMatrix::SetBorder(quint32 Color)
{
    SetLine( 0, Color) ;
    SetLine( WorkMatrix->height()-1 , Color) ;
    SetColumn(0, Color) ;
    SetColumn( WorkMatrix->width()-1,Color) ;
}

void MathMatrix::SetBorder(QColor NamedColor)
{
    QColor TempColor(NamedColor);
    SetLine( 0, TempColor) ;
    SetLine( WorkMatrix->height()-1 , TempColor) ;
    SetColumn(0, TempColor) ;
    SetColumn( WorkMatrix->width()-1,TempColor) ;
}

QImage  MathMatrix::ColShift(int Offset)
{
   return( WorkMatrix->transformed(QTransform().translate(Offset,0)) );
}

void MathMatrix::LineShift( int Offset )
{
   *WorkMatrix = WorkMatrix->transformed(QTransform().translate(0,Offset)) ;
}

QImage  MathMatrix::Rotate(int Angle)
{
    return(  WorkMatrix->transformed(QTransform().rotate(Angle)) );
}

void MathMatrix::Invert()
{
   WorkMatrix->invertPixels();
}

// Goal : when you are happy with pattern, you need to "take a picture" of it and
// save it into a sequence list.
//Parse the matrix and retrieve the color for each of the points in a 2D (row,cols) Vector

//  Format: vector<std::vector<QRgb>> array_2d(rows, std::vector<QRgb>(cols, 0));

void MathMatrix::CopyPatternToSequence( QVector<QVector<QRgb>> &MatrixVector)
{
    for ( int row = 0; row < WorkMatrix->height() ; ++row )
        for ( int col = 0; col < WorkMatrix->width(); ++col )
        {
            QVector<QRgb> inner_vector;
            inner_vector.push_back( GetPoint(row,col) );
            MatrixVector.push_back(inner_vector);
        }
}



void MathMatrix::TestMatrix()
{
    qDebug() << "TestMatrix : " << WorkMatrix->width() << " - " << WorkMatrix->height();
    for(int i=0; i< WorkMatrix->width();++i )
    {
       // for (int j=0; j< WorkMatrix->height();++j )
            qDebug() <<  QString::number( WorkMatrix->pixel(i,0), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,1), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,2), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,3), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,4), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,5), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,6), 16 )
                     <<  QString::number( WorkMatrix->pixel(i,7), 16 )  ;
    }
}

