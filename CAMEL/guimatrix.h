#ifndef GUIMATRIX_H
#define GUIMATRIX_H

#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QErrorMessage>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>

#include "projectmatrix.h"

class GuiMatrix: public QButtonGroup
{
    Q_OBJECT
private :
        int MatxRows;
        int MatxCols;
        QVector<QVector<QRgb> > Project_VectorMtx() ;

public:
    QVector<QVector<QRgb> >* truc{} ;
    QGridLayout *Glayout;
    GuiMatrix(int Rows, int Cols, int Led_colors, QWidget *parentWidget, QVector<QVector<QRgb> > &Proj_VectorMatrix);
    ~GuiMatrix();
    void Populate(QGridLayout *layout, const int rows, const int cols)                       ;

public slots:
    void buttonClick(QAbstractButton* button) ;
};

#endif // GUIMATRIX_H
