#ifndef GUIMATRIX_H
#define GUIMATRIX_H

#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>

class GuiMatrix: public QButtonGroup
{
    Q_OBJECT
private :
public:
    GuiMatrix(int Rows, int Cols, int Led_colors, QWidget *parentWidget);
    ~GuiMatrix();

public slots:
    void buttonClick(QAbstractButton* button) ;
};

#endif // GUIMATRIX_H
