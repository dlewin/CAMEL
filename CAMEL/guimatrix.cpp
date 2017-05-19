#include "guimatrix.h"
#include "matrixbutton.h"
#include <QDebug>

#define BTNCOLOR_GREY 10526880

GuiMatrix::GuiMatrix(uint Rows, uint Cols, quint32 Led_colors, QWidget * parentWidget, QVector< QPair<QString, QRgb> >& ColorsList )
    : MatxRows(Rows),
      MatxCols(Cols),
      GUIMtx_BtnColorsArray(MatxRows * MatxCols, BTNCOLOR_GREY),
      Palette()
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

    /* A model will either have:
     *  - a color depth, ie: the total number of colors
     *  - a colors list: a list of the named colors
     */
    if ( ColorsList.size() ==0 )
    {
        for (uint ind; ind <Led_colors; ind++)
            Palette[ind]= ind ;
    }
    else
    {
         for (auto iter: ColorsList )
         {
            Palette<< iter.second ;
            qDebug()<< "couleur:"<< iter.second ;
          }
    }

    parentWidget->setLayout(layout)                                                     ;
    connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));


}

void GuiMatrix::Populate(QGridLayout *layout, const int rows, const int cols)
{
    for ( int i = 0; i < rows; ++ i)
    {
        for ( int j = 0; j < cols; ++j)
        {
            MatrixButton *btn= new MatrixButton();
            btn->setFixedWidth(20);
            btn->setStyleSheet("QPushButton{background-color:#A0A0A0;}"
                               "QPushButton[_rightClicked = true]{background-color:#A0A0A0;}")      ;

            layout->addWidget(btn,i,j)                                ;

            this->addButton(btn)                              ;
        }
    }
}

QRgb GuiMatrix::GetButtonColor(int Btn_ID)
{
    return GUIMtx_BtnColorsArray[Btn_ID] ;
}

void GuiMatrix::buttonClick(QAbstractButton* button)
{
    int BtnID= abs(this->id(button)) -2 ;

    QRgb BtnColorValue = GUIMtx_BtnColorsArray[BtnID];

    int indexPalette = Palette.indexOf(BtnColorValue) ;

    if (BtnColorValue == BTNCOLOR_GREY)                                // The 1st time the let button is grey (off)
        GUIMtx_BtnColorsArray[BtnID]= Palette.first() ;
    else if (indexPalette != -1 )                                      // we have found the color in the list
    {
        if ( Palette[indexPalette] == Palette.last() )
            GUIMtx_BtnColorsArray[BtnID]= Palette.first() ;
        else
            GUIMtx_BtnColorsArray[BtnID]= Palette[++indexPalette] ;
    }
    else
        qDebug() << "buttonClick problem, the color is not in the Palette list: " <<BtnColorValue ; // if not: there is a problem


    BtnColorValue = GUIMtx_BtnColorsArray[BtnID] ;
    QString ColorString = "QPushButton{background-color: " +   QString("#%1").arg(BtnColorValue, 6, 16, QLatin1Char( '0' ))  + ";} "
                          "QPushButton[_rightClicked = true]{background-color:#A0A0A0;} ";

    button->setStyleSheet(ColorString)  ;
}


void GuiMatrix::mousePressEvent(QEvent *event)
{
    if(  this->event(event) != Qt::LeftButton )
    {
        qDebug()<< "Right click" ;
    }

}

GuiMatrix::~GuiMatrix()
{
}


