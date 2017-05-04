#ifndef PROJECTMATRIX_H
#define PROJECTMATRIX_H

#include <QFile>

#include "matrix.h"
#include "configurationmanager.h"
#include "sequencemanager.h"

class ProjectMatrix
{
private:
    MathMatrix ProjMatrix ;
    quint16 Cols={};
    quint16 Rows={};
    quint32 ColorDepth={} ;
    void TestReadVector( QVector<QVector<QRgb> > &MatrixVector);
public:
    static QVector<QVector<QRgb>> Proj_VectorMatrix;
    int CurVector_Index;
    ProjectMatrix(const QString M_Name, const quint16 M_Rows, const quint16 M_Cols, const quint32 M_ColorsDepth);
    void AppendPattern(MathMatrix ImgToRead, QVector<QVector<QRgb> > &MatrixVector);
    int SavePattern(QString Filename, QVector<QVector<QRgb> > &MatrixVector);
    int LoadPattern(QString Filename, QVector<QVector<QRgb> > &MatrixVector);
    void append(QVector<QRgb> &Pattern );
    int RemoveLastPattern(QVector<QVector<QRgb> > &MatrixVector) ;
    void RemoveAllPatterns(QVector<QVector<QRgb> > &MatrixVector );
};

#endif // PROJECTMATRIX_H
