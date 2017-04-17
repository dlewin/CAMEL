#include "projectmatrix.h"



ProjectMatrix::ProjectMatrix(const QString MName="Matrix Name",const quint16 MCols=8 ,const quint16 MRows=8, const quint16 MColors=3 )
    :MathMatrix{MName, MCols, MRows, MColors}//,Pattern{},SequenceManager{},ConfigurationManager{}
{
  qDebug() << MName ;
}
