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

    Populate(Glayout,Rows,Cols);

    connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));


}

void GuiMatrix::Populate(QGridLayout *layout, const int rows, const int cols)
{
    for (uint i = 0; i < rows; ++ i)
    {
     for (uint j = 0; j < cols; ++j)
     {
      QString index = QStringLiteral("(%1,%2)").arg(i).arg(j)   ;
      QPushButton* btn = new QPushButton("-")                 ;
      btn->setFixedWidth(20);
      btn->setStyleSheet("background-color:grey;")              ;
      layout->addWidget(btn,i,j)                                ;

      this->addButton(btn)                              ;
     }
    }
}

void GuiMatrix::buttonClick(QAbstractButton* button)
{
}

GuiMatrix::~GuiMatrix()
{
}
