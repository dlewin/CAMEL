#include "guimatrix.h"

GuiMatrix::GuiMatrix(int Rows, int Cols, int Led_colors, QWidget *parentWidget)
{
    // Let's create the HMI that accepts click as input and also represent the MainMatrix states
// MyButtonGroup* group   = new MyButtonGroup(centralWidget)   ;
    setParent(parentWidget)  ;

    QVBoxLayout *layout     = new QVBoxLayout(parentWidget)                             ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                                         ;
    QGridLayout *Glayout    = new QGridLayout()                                         ;
    Glayout->setSpacing(0)                                                              ;
    Hlayout->addStretch(1)                                                              ;
    Hlayout->addLayout(Glayout)                                                         ;
    Hlayout->addStretch(1)                                                              ;
    layout->addLayout(Hlayout)                                                          ;
    layout->addStretch(1)                                                               ;

    parentWidget->setLayout(layout)                                                     ;
connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));

}

void GuiMatrix::buttonClick(QAbstractButton* button)
{
}

GuiMatrix::~GuiMatrix()
{
}
