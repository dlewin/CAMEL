#include "guimatrix.h"
#include "projectmatrix.h"


#define BTNCOLOR_GREY "#808080"
#define BTNCOLOR_ORANGE "#ffa500"
#define BTNCOLOR_GREEN "#008000"


GuiMatrix::GuiMatrix(int Rows, int Cols, int Led_colors,QWidget * parentWidget)
{
    // Let's create the HMI that accepts click as input and also represent the MainMatrix states
    setParent(parentWidget)  ;

    QVBoxLayout *layout     = new QVBoxLayout()                             ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                                         ;
    QGridLayout *Glayout    = new QGridLayout()                                         ;
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

void GuiMatrix::buttonClick(QAbstractButton* button)
{
    QColor  Btn_Color = button->palette().color(QPalette::Button) ;
    QString BtnColorName= Btn_Color.name();

    if (BtnColorName == BTNCOLOR_GREY)
    {
        button->setStyleSheet("background-color:green;")     ;
    }
    else if (BtnColorName == BTNCOLOR_GREEN )
    {
        button->setStyleSheet("background-color:orange;")    ;
    }
    else if (BtnColorName == BTNCOLOR_ORANGE)
    {
        button->setStyleSheet("background-color:red;")       ;
    }
    else
    {
        button->setStyleSheet("background-color:grey;")      ;
    }
}

GuiMatrix::~GuiMatrix()
{
}


