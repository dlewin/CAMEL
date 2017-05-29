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


class GuiMatrix: public QButtonGroup
{
    Q_OBJECT
private :
    uint MatxRows;
    uint MatxCols;
    QVector<QRgb> GUIMtx_BtnColorsArray  ;       // Creating the internal color representation of the buttons matrix, assigned as Grey
    QVector<QRgb> Palette ;

public:
    void Reset(uint Rows, uint Cols, quint32 Led_colors,QVector<QPair<QString, QRgb> > &ColorsList);
    QRgb GetButtonColor(int Btn_ID)    ;
    QGridLayout *Glayout;
    GuiMatrix(uint Rows, uint Cols, quint32 Led_colors, QWidget *parentWidget, QVector<QPair<QString, QRgb> > &ColorsList);
    ~GuiMatrix();
    void Populate(QGridLayout *layout, const int rows, const int cols)                       ;
    void Colorize(int BtnPos, QRgb CurValue) ;
    void Clear();
    void Fill(QRgb BtnColorValue) ;

public slots:
    void buttonClick(QAbstractButton* button) ;
    void onrightClicked() ;
};

#endif // GUIMATRIX_H
