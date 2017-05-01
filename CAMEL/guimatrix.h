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
public:
    GuiMatrix(int Rows, int Cols, int Led_colors, QWidget *parentWidget);
    ~GuiMatrix();
    void Populate(QGridLayout *layout, const int rows, const int cols)                       ;
//    QLabel *colorLabel;
//    QErrorMessage *errorMessageDialog;

public slots:
    void buttonClick(QAbstractButton* button) ;
//    void setColor();
//    void criticalMessage(QWidget *parentWidget);
//    void informationMessage(QWidget *parentWidget);
//    void questionMessage(QWidget *parentWidget);
//    void warningMessage(QWidget *parentWidget);
//    void errorMessage();

};

#endif // GUIMATRIX_H
