#include "guimatrix.h"
#include <QDebug>

#define BTNCOLOR_GREY 8421504
#define BTNCOLOR_ORANGE 16753920
#define BTNCOLOR_GREEN 32768
#define BTNCOLOR_RED 8388608

GuiMatrix::GuiMatrix(int Rows, int Cols, int Led_colors,QWidget * parentWidget, QVector<QVector<QRgb> > &Proj_VectorMatrix )
    : truc(&Proj_VectorMatrix),        MatxRows(Rows),         MatxCols(Cols)
{
    // Let's create the HMI that accepts click as input and also represent the MainMatrix states
    setParent(parentWidget)  ;

    QVBoxLayout *layout     = new QVBoxLayout()                             ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                                         ;
    Glayout    = new QGridLayout()                                         ;
    Glayout->setSpacing(0)                                                              ;
    Hlayout->addStretch(1)                                                              ;
    Hlayout->addLayout(Glayout)                                                         ;
    Hlayout->addStretch(1)                                                              ;
    layout->addLayout(Hlayout)                                                          ;
    layout->addStretch(1)                                                               ;

    Populate(Glayout,Rows,Cols);

   connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));

 parentWidget->setLayout(layout)                                                     ;
}

void GuiMatrix::Populate(QGridLayout *layout, const int rows, const int cols)
{
    for ( int i = 0; i < rows; ++ i)
    {
     for ( int j = 0; j < cols; ++j)
     {
      QPushButton* btn = new QPushButton(" ")                 ;
      btn->setFixedWidth(20);
      btn->setStyleSheet("background-color:grey;")              ;
      layout->addWidget(btn,i,j)                                ;

      this->addButton(btn)                              ;
     }
    }
}


///TODO need to manage the colors declared from model (only 3 here)
void GuiMatrix::buttonClick(QAbstractButton* button)
{
    QColor  Btn_Color = button->palette().color(QPalette::Button) ;
//    QString BtnColorName= Btn_Color.name();
    int BtnColorValue= Btn_Color.value() ;
    QRgb CurrentBtnColor ;

    if (BtnColorValue == BTNCOLOR_GREY)
    {
        button->setStyleSheet("background-color:green;")     ;
        CurrentBtnColor = BTNCOLOR_GREEN;
    }
    else if (BtnColorValue == BTNCOLOR_GREEN )
    {
        button->setStyleSheet("background-color:orange;")    ;
        CurrentBtnColor = BTNCOLOR_ORANGE;
    }
    else if (BtnColorValue == BTNCOLOR_ORANGE)
    {
        button->setStyleSheet("background-color:red;")       ;
        CurrentBtnColor = BTNCOLOR_RED;
    }
    else
    {
        button->setStyleSheet("background-color:grey;")      ;
        CurrentBtnColor = BTNCOLOR_GREEN;
    }

    int BtnID= abs(this->id(button)) -2 ;
    int Current_Row,Current_Col ;


   qDebug()<< "truc" << truc[0][0] << BtnID ;
}

GuiMatrix::~GuiMatrix()
{
}


