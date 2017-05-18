#include "guimatrix.h"
#include <QDebug>

#define BTNCOLOR_GREY 32768
#define BTNCOLOR_ORANGE 16753920
#define BTNCOLOR_GREEN 8421504
#define BTNCOLOR_RED 8388608

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
        for (int ind; ind <Led_colors; ind++)
            Palette[ind]= ind ;

        qDebug()<< "Palette (Led_colors) =" << Palette <<" " <<Led_colors ;
    }
    else
    {
         for (auto iter: ColorsList )
         {
            Palette<< iter.second ;
          }

         qDebug()<< "Palette (ColorsList) =" << Palette.size() << "ColorsList.size " << ColorsList.size() ;
         for (auto iter: Palette)
             qDebug() << iter ;
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
      QPushButton* btn = new QPushButton(" ")                 ;
      btn->setFixedWidth(20);
      btn->setStyleSheet("background-color:grey;")              ;
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

    uint Current_Row= BtnID/8 ;
    uint Current_Col = BtnID -(8*Current_Row);

    int indexPalette = Palette.indexOf(BtnColorValue) ;
    if ( Palette[indexPalette] == Palette.last() )
         GUIMtx_BtnColorsArray[BtnID]= Palette.first() ;
    else
         GUIMtx_BtnColorsArray[BtnID]= Palette[++indexPalette] ;

    BtnColorValue = GUIMtx_BtnColorsArray[BtnID] ;
    QString ColorString = "background-color: " +   QString("#%1").arg(BtnColorValue, 6, 16, QLatin1Char( '0' ))  + ";";

    button->setStyleSheet(ColorString)  ;
}


void GuiMatrix::mousePressEvent(QEvent *event)
{
    if(  this->event(event) == Qt::RightButton)
    {
        qDebug()<< "Right click" ;
    }

}

GuiMatrix::~GuiMatrix()
{
}


