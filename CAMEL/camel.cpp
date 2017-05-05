#include "camel.h"

#include "ui_camel.h"

Camel::Camel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camel)
{
    ui->setupUi(this);
    setDockNestingEnabled(true);
    QWidget *MatrixGui = new QWidget();

    CreateDock();
    int Rows=8,Cols=8, ColorDepth=3 ; //Debug: will be provided by the wizard and given for ProkectMatrix Instanciation
    GuiMatrix* Matrix_8x8x3 = new GuiMatrix(Rows,Cols,ColorDepth,MatrixGui );

    setCentralWidget(MatrixGui);

    SaveToFile("Camel.ini",Rows, Cols) ;
    LoadFromFile("Camel.ini") ;


//    ProjectMatrix* workMatrix   = new ProjectMatrix("Adafruit Bicolors I2C Leds Matrix", 8,8,3);


}


bool Camel::LoadFromFile(QString InifileName)
{
    QSettings settings( InifileName , QSettings::IniFormat ) ;
    QFile Inifile(InifileName) ;

    if ( !Inifile.exists() )        // Checks if the ini file exists
    {
        qDebug() << "The file" << Inifile.fileName() << "does not exist.";
        return false;
    }


     QStringList ModelsList, ModelText ;
     settings.beginGroup("Models");
        {
              ModelsList << settings.childKeys()                            ;
              foreach (const QString &childKey, ModelsList)
              {
                  ModelText <<  settings.value(childKey).toString()                      ;
              }
          }
     settings.endGroup();

//    QVector<Matrix_Model> AllModels ;

     for (auto it2: ModelsList)
     {
         Matrix_Model Temp_Model;
         Temp_Model.Name= QString(it2) ;

         settings.beginGroup(it2);
            for (auto iter :settings.allKeys() )
            {
               QString buffer= iter ;
               if (buffer.contains("Colors/"))      // Looking for a Color List Name = Value
               {
                   QString ColorName = buffer.remove(QRegExp("Colors/"));
                   QColor ColorValue=  QColor(settings.value(iter).toInt()) ;

                Temp_Model.ColorsList << QPair<QString, QColor> ( ColorName,ColorValue ) ;
//                   qDebug()<< "Colors: " <<  buffer.remove(QRegExp("Colors/")) << ".=." << settings.value(iter).toString() ;
               }
               else
               {
                   if ( buffer.contains("Cols") )
                       Temp_Model.Cols = settings.value(iter).toUInt();
                   else if ( buffer.contains("Rows") )
                        Temp_Model.Rows = settings.value(iter).toUInt() ;
                   else if ( buffer.contains("colorsdepth") )                        // Looking for a ColorDepth = Value
                        Temp_Model.ColorsDepth = settings.value(iter).toUInt() ;
//                   qDebug() << buffer << "=>" <<settings.value(iter).toString()  ;
               }
            }

         settings.endGroup();

         // We now have all the elements to create a complete model
       MatrixModels.push_back(Temp_Model );

     }

     for ( int i=0; i<MatrixModels.size(); i++)
     {
        qDebug() << MatrixModels[i].Name  <<" / "<< MatrixModels[i].ColorsDepth <<" / "<< MatrixModels[i].ColorsList ;
     }

    return true ;
}


/* Models section is where each model, ie: the physical leds matrix, is described
 a model is :

    [Models]
    name = rowsxcolsxcolors

 Sequence section is the container of the patterns Sequence
 Each sequence must have at least :

    [SequenceName]
    Patterns=Patterns1.bin
    Compatibility=8x8@3
    1=Pattern1

 and eventually:
    2=tempo500
    3=Pattern3
    ....
*/

bool Camel::SaveToFile(const QString InifileName, quint16 Rows ,quint16 Cols  )
{
    QSettings settings( InifileName, QSettings::IniFormat )                     ;
    settings.beginGroup("Models")                                                       ;
        settings.setValue( "Adafruit_BicolorLEDSquarePixel" , "2 Colors Leds Matrix" )        ;
        settings.setValue( "SenseHat" , "The SenseHat" )        ;
    settings.endGroup()                                                        ;
    settings.beginGroup("Adafruit_BicolorLEDSquarePixel") ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors/Red", "8388608");
        settings.setValue( "Colors/Green","32768");
        settings.setValue( "Colors/Orange","16753920");
    settings.endGroup()                                                        ;
    settings.beginGroup("SenseHat") ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "colorsdepth","16777215");
    settings.endGroup()  ;
    settings.beginGroup("Sequence1")                                               ;
        settings.setValue( "File" , "Pattern1.bin" ) ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors","000003");
        settings.setValue ( "1","Pattern1" ) ;
    settings.endGroup()                                                        ;

    return true ;
}



Camel::~Camel()
{
    delete ui;
}

void Camel::CreateDock()
{
    // First dock in the left top corner
    QDockWidget *dockWidget = new QDockWidget("--- 1 ---");
    dockWidget->setWidget(new QTextEdit);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    // Second dock below first one
    QDockWidget *dockWidget2 = new QDockWidget("--- 2 ---");
    dockWidget2->setWidget(new QPushButton );
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget2);

    // Third in tab with second one
    QDockWidget *dockWidget3 = new QDockWidget("--- 3 ---");
    dockWidget3->setAllowedAreas(Qt::RightDockWidgetArea) ;

    QListWidget *ColorList = new QListWidget  ;
    ColorList->insertItem(0,"1ER Label");
    ColorList->insertItem(1,"2ER Label");
    ColorList->item(0)->setForeground(*(new QBrush(Qt::red)));
    ColorList->item(0)->setBackground(*(new QBrush(Qt::green)));

    dockWidget2->setWidget(ColorList);

    addDockWidget(Qt::RightDockWidgetArea, dockWidget3);


    QPixmap matrix(":/matrix_icon");
    QPixmap wizard(":/wizard");
    QPixmap magic(":/magic");
    QPixmap colors(":/colors");

    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->addAction(QIcon(matrix), "test");
    toolbar->addAction(QIcon(wizard), "New Matrix");
    toolbar->addAction(QIcon(magic), "New Matrix");

    Wizard_Action =toolbar->addAction (QIcon(wizard), "Wizard");
    connect(Wizard_Action, SIGNAL(triggered()), this, SLOT(Wizard() ));

     SelectColors_Action =toolbar->addAction (QIcon(colors), "Select color");
     connect(SelectColors_Action, SIGNAL(triggered()), this, SLOT(color_selector() ));
}
int Camel::Wizard()
{
    QStringList items;
    items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Matrix Selection"),
                                         tr("Model:"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        qDebug() << "item:" << item;
        return 0 ;
    }
    return -1 ;
}

void Camel::color_selector()
{

    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        qDebug() << "Color Choosen : " << color.name();
    }
}

