#include "camel.h"

#include "ui_camel.h"

#define MAGIC_NUMBER            0xDEADFACE
#define BIN_FILE_VERSION        1
#define ERR_BAD_FILE_FORMAT     -1
#define ERR_BAD_FILE_TOO_OLD    -2
#define ERR_BAD_FILE_TOO_NEW    -3
#define ERR_MTX_FMT_UNKNOWN     -4

#define EMPTY_SEQUENCE          -11


///NOTE : For the network sender = the code is in MyButtonGroup.Send

Camel::Camel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camel)
{
    ui->setupUi(this);
    MatxRows= MatxCols = 8 ;
    setDockNestingEnabled(true);
//    SequenceVect;

    QWidget *MatrixGui = new QWidget();
    setCentralWidget(MatrixGui);

    MatrixGui->resize(3,3);
        // Create default instances
    QVector< QPair<QString, QRgb> > ColorsL = {{"Color1",16724787},{"Color2",65280},{"Color3",16753920},{"EraseColor",10526880}} ;
    CurrentGUIMatrix = new GuiMatrix(MatxRows,MatxCols,3,MatrixGui, ColorsL );

    CreateDock();           // This MUST be defined after GUIMatrix to be able to call it thereafter
}


void Camel::onListRightClicked()
{
    qDebug()<< "Right clicked" ;
}

void Camel::LoadingConfig()
{
    LoadConfig();
}

bool Camel::LoadConfig()
{
    QString InifileName = QFileDialog::getOpenFileName(this,
        tr("Open Matrix configuration"), "", tr("Matrix Config Files (*.mtx);;All Files (*)") );

    if ( InifileName.isEmpty() )        // Checks if the ini file exists
    {
        qDebug() << "No file selected";
        return false;
    }

    QSettings settings( InifileName , QSettings::IniFormat ) ;

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
                   QRgb ColorValue=  QRgb(settings.value(iter).toUInt()) ;

                Temp_Model.ColorsList << QPair<QString, QRgb> ( ColorName,ColorValue ) ;
               }
               else
               {
                   if ( buffer.contains("Cols") )
                       Temp_Model.Cols = settings.value(iter).toUInt();
                   else if ( buffer.contains("Rows") )
                        Temp_Model.Rows = settings.value(iter).toUInt() ;
                   else if ( buffer.contains("colorsdepth") )                        // Looking for a ColorDepth = Value
                        Temp_Model.ColorsDepth = settings.value(iter).toUInt() ;
               }
            }

         settings.endGroup();

         // We now have all the elements to create a complete model
       MatrixModels.push_back(Temp_Model );

     }
            //Testing
     for ( int i=0; i<MatrixModels.size(); i++)
     {
        qDebug() << MatrixModels[i].Name  <<" / "<< MatrixModels[i].ColorsDepth <<" / "<< MatrixModels[i].ColorsList ;
     }

    return true ;
}

void Camel::SavingConfig()
{
    QString InifileName = QFileDialog::getSaveFileName(this,
                                                       tr("Save Matrix configuration"), "",
                                                       tr("Matrix Config Files (*.mtx);;All Files (*)")
                                                      );

    if ( InifileName.isEmpty() )        // Checks if the ini file exists
        qDebug() << "No file selected for saving";
    else
        SaveConfig(InifileName, MatxRows, MatxCols ) ;
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

bool Camel::SaveConfig(const QString InifileName, quint16 Rows ,quint16 Cols  )
{
    QSettings settings( InifileName, QSettings::IniFormat )                     ;
    settings.beginGroup("Models")                                                       ;
        settings.setValue( "Adafruit_BicolorLEDSquarePixel" , "2 Colors Leds Matrix" )        ;
        settings.setValue( "SenseHat" , "The SenseHat" )        ;
    settings.endGroup()                                                        ;
    settings.beginGroup("Adafruit_BicolorLEDSquarePixel") ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors/Red",   "16724787");
        settings.setValue( "Colors/Green", "65280");
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
    // Icons from resources
    QPixmap matrix(":/matrix_icon");
    QPixmap wizard(":/wizard");
    QPixmap magic(":/magic");
    QPixmap colors(":/colors");
    QPixmap loadconfig(":/loadconfig");
    QPixmap saveconfig(":/saveconfig");
    QPixmap runsequence(":/runsequence");
    QPixmap clearmatrix(":/clearmatrix");
    QPixmap fillmatrix(":/fillmatrix");

    ///NOTE For MVD List, check example:
    /// http://doc.qt.io/qt-5/qtwidgets-itemviews-puzzle-mainwindow-cpp.html
    ///

            // 2nd dock item ---------------------------------------------
    QDockWidget *dockWidget2 = new QDockWidget("--- 2 ---");
    dockWidget2->setWidget(new QPushButton );
    QListWidget *ColorList = new QListWidget  ;
    ColorList->insertItem(0,"1ER Label");
    ColorList->insertItem(1,"2ER Label");
    ColorList->item(0)->setForeground(*(new QBrush(Qt::red)));
    ColorList->item(0)->setBackground(*(new QBrush(Qt::green)));
    dockWidget2->setWidget(ColorList);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget2);

        // 3rd dock item----------------------------------------------
    QDockWidget *dockWidget3 = new QDockWidget("--- 3 ---");
    dockWidget3->setAllowedAreas(Qt::RightDockWidgetArea) ;

    SequenceList = new QListWidget  ;
    dockWidget3->setWidget(SequenceList);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget3);

        // Toolbar set up
    QToolBar *toolbar = addToolBar("main toolbar");

    Wizard_Action =toolbar->addAction(QIcon(wizard), "Wizard");        // Manage Wizard Action
    connect(Wizard_Action, SIGNAL(triggered()), this, SLOT(Wizard() )); // and its event

    SelectColors_Action =toolbar->addAction(QIcon(colors), "Select color");           // Manage Color Action
    connect(SelectColors_Action, SIGNAL(triggered()), this, SLOT(color_selector() ));  // and its event

    SaveGUIPattern_Action =toolbar->addAction(QIcon(matrix), "Save the current Pattern");           // Manage the Pattern save Action
    connect(SaveGUIPattern_Action, SIGNAL(triggered()), this, SLOT(PushGUIPattern_ToSequence() ));  // and its event

    SequenceList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(SequenceList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    LoadFile_Action =toolbar->addAction(QIcon(loadconfig), "Load a configuration") ;           // Manage Load configuration Action
    connect(LoadFile_Action, SIGNAL(triggered()), this, SLOT(LoadingConfig() ))     ;           // and its event

    SaveFile_Action =toolbar->addAction(QIcon(saveconfig), "Save a configuration") ;
    connect(SaveFile_Action, SIGNAL(triggered()), this, SLOT(SavingConfig() ))     ;

    RunSequence_Action =toolbar->addAction(QIcon(runsequence), "Play the sequence") ;
    connect(RunSequence_Action, SIGNAL(triggered()), this, SLOT(PlayingSequence() ))     ;

    ClearMtx_Action =toolbar->addAction(QIcon(clearmatrix), "Clear the Matrix") ;
    connect(ClearMtx_Action, SIGNAL(triggered()), this, SLOT(ClearMatrix() ))     ;

    FillMtx_Action =toolbar->addAction(QIcon(fillmatrix), "Fill all the Matrix with a color") ;
    connect(FillMtx_Action, SIGNAL(triggered()), this, SLOT(FillMatrix() ))     ;

}


/* Visualizer : plays all patterns that are in the SequenceList  */

void Camel::PlayingSequence()
{

//     for (int ind=0; ind< SequenceVect.size(); ind++ )
//     {
//        CurrentGUIMatrix->Colorize( SequenceVect[ind]);
//        qDebug() << "play no " <<  ind ;
//     }

     for ( int indRow = 0; indRow < SequenceVect.size()  ; ++indRow )
         for ( int indCol = 0; indCol <SequenceVect[indRow].size() ; ++indCol )
         {
               CurrentGUIMatrix->Colorize(indRow, SequenceVect[indRow][indCol]) ;
         }

}

void Camel::FillMatrix()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {

        CurrentGUIMatrix->Fill(color.rgb() );
    }
}

void Camel::ClearMatrix()
{
 CurrentGUIMatrix->Clear();
}

/* we need to realize slots for adding and removing QListWidget elements
    we iterate all selected items (for set multiple selection mode use setSelectionMode() method) and delete it by ourself, because docs says that
    Items removed from a list widget will not be managed by Qt, and will need to be deleted manually. */

void Camel::eraseItem()
{
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < SequenceList->selectedItems().size(); ++i)
    {
        int CurRow = SequenceList->currentRow() ;
        QListWidgetItem *item = SequenceList->takeItem( CurRow);  // Get curent item on selected row
        delete item;        // And remove it
        SequenceVect.removeAt(CurRow);
    }
}

void Camel::addItem()
{
       PushGUIPattern_ToSequence();
}


void Camel::ClearList()
{
    SequenceList->clear();
    SequenceVect.clear();
}

void Camel::showContextMenu(const QPoint &pos)
{
    // Handle global position
        QPoint globalPos = SequenceList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        myMenu.addAction("Insert", this, SLOT(addItem()));
        myMenu.addAction("Erase",  this, SLOT(eraseItem()));
        myMenu.addAction("Clear all",  this, SLOT(ClearList()));

        // Show context menu at handling position
        myMenu.exec(globalPos);
}

void Camel::MatrixSnapshot(QImage &imageTest, uint BtnID, QRgb BtnCol )
{
    // Let's create Image as the extract for the current Matrix
    uint GridWith  = imageTest.width() ;

    QPainter p;
    p.begin(&imageTest);
        uint step= GridWith/MatxCols ;

            // now let's copy the current Pattern into the grid
        p.setPen(QPen(QColor(Qt::gray )));
        p.setBrush(QBrush(QColor( BtnCol )));
        uint Current_Row= BtnID/8 ;
        uint Current_Col = BtnID -(8*Current_Row);
        p.drawRect( QRect(Current_Col*step, Current_Row*step, step-1,step-1)) ; // -1 : nicer if a rectangle is < grid rect dims
    p.end();
}

/* Goal : when you are happy with pattern, you need to "take a picture" of it and
 save it into a sequence list.
 Parse the GUImatrix and retrieve the color for each of the points in a 2D Vector  */

void Camel::PushGUIPattern_ToSequence()
{
    QImage imageTest(40,40, QImage::Format_RGB32);
    QVector<QRgb> row_vector;

    for ( uint BtnID = 0; BtnID < MatxRows*MatxCols; BtnID++ )
    {
        QRgb BtnColor= CurrentGUIMatrix->GetButtonColor(BtnID)   ;
        row_vector.push_back(  BtnColor  );
        MatrixSnapshot(imageTest,BtnID, BtnColor ) ;
    }

    SequenceVect.push_back(row_vector);

    // Create a snapshot to GUI
    QString PatSring = "Pattern" + QString::number(SequenceList->count() +1) ;     // Retrieve the order of the pattern
    QListWidgetItem *SnapshotItem = new QListWidgetItem(PatSring, SequenceList);
    SnapshotItem->setData(Qt::DecorationRole, QPixmap::fromImage(imageTest));
    SequenceList->insertItem(1, SnapshotItem);
}

int Camel::Wizard()
{

    QStringList items;
    for ( int i=0; i<MatrixModels.size(); i++)
        items << MatrixModels[i].Name ;

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Matrix Selection"),
                                         tr("Select a model:"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        int ColorNb ;
        int Model_index = -1;
        for ( int i=0; i<MatrixModels.size(); i++)
        {
            if ( item.compare( MatrixModels[i].Name ) ==0 )       // Look for the selected model
                Model_index = i;
        }

        // Compute the colors or colordepth
        if( MatrixModels[Model_index].ColorsList.size() !=0)
            ColorNb= MatrixModels[Model_index].ColorsList.size() ;
        else if (MatrixModels[Model_index].ColorsDepth !=0 )
            ColorNb =  MatrixModels[Model_index].ColorsDepth ;
        else return -2 ;                                    // Error: nothing about colors from the model

        MatxRows = MatrixModels[Model_index].Rows;
        MatxCols = MatrixModels[Model_index].Cols ;

        /// FIXME need to resize matrix and GUImatrix from wizard & from LoadSequence
        //        QWidget *MatrixGui = new QWidget();
        //        setCentralWidget(MatrixGui);

        ColorsL.clear();
        ColorsL = MatrixModels[Model_index].ColorsList ;

        return 0 ;
    }
    return -1 ;
}



// Save all the patterns in the 2D Vector into the Sequence binary file

int Camel::SaveSequence(QString Filename, QVector<QVector<QRgb>> &MatrixVector)
{
    if (MatrixVector.isEmpty() )
        return EMPTY_SEQUENCE ;

    QFile fileout(Filename);
    if (fileout.open( QFile::WriteOnly ))
    {
        QDataStream out(&fileout);
        // Header
        out << (quint32) MAGIC_NUMBER ;             // Magic Number
        out << (quint16) BIN_FILE_VERSION;
        out << (quint16) MatrixVector.size() - 1;  // Tells how much patterns this sequence file have
        out << (quint16) MatxRows;
        out << (quint16) MatxCols;
//        out << (quint32) MatrixModels[Model_index].ColorsDepth;


        // now save the Patterns Data from the 2D Vector
        for(int i = 0;i < MatrixVector.size();++i)
        {
              for(int j = 0;j < MatrixVector[i].size();++j)
              {
                 out <<  MatrixVector[i][j] ;
              }
        }
        fileout.close();
    }
    return 0;
}

int Camel::LoadSequence(QString Filename, QVector<QVector<QRgb> > &MatrixVector)
{
    QFile filein(Filename);
    if (!filein.open(QIODevice::ReadOnly))
            return -1;

    QDataStream in(&filein);

    // Read and check the header
    quint32 magic;
    in >> magic;
    if (magic != MAGIC_NUMBER)
        return ERR_BAD_FILE_FORMAT;

    // Read the version
    quint16 version;
    in >> version;
    if (version < BIN_FILE_VERSION)
        return ERR_BAD_FILE_TOO_OLD;
    if (version > BIN_FILE_VERSION)
        return ERR_BAD_FILE_TOO_NEW;

    // Retrieve the sequence size ( how much patterns)
    quint32 SeqSize ;
    in >> SeqSize ;

    //    MatrixFormat
    quint16 SeqFileRows, SeqFileCols ;
    quint32 SeqFileColors ;
    in >> SeqFileRows;
    in >> SeqFileCols;
    in >> SeqFileColors;

    // Check the dims of the matrix in the seq file
    if ( SeqFileRows!=8 && SeqFileCols!=8 && SeqFileColors!=3 )
        return ERR_MTX_FMT_UNKNOWN ;                                ///WARNING Matrix other than 8x8@3 are not handled

    QVector<QVector<QRgb> > Temp_MatrixVector;
    QRgb RGBValue = 0 ;

    for(uint i = 0; i < SeqSize; ++i)
    {
        for(uint indRow = 0;indRow < SeqFileRows; ++indRow )
        {
            for(uint indCol = 0;indCol < SeqFileCols ;++indCol)
            {
                QVector<QRgb> inner_vector;
                in >> RGBValue;

                inner_vector.push_back(RGBValue);
                Temp_MatrixVector.push_back(inner_vector);
            }
        }
    }

    MatrixVector = Temp_MatrixVector ;                      // now everything is ok : copy the  temp vector to the current working one
    return 0 ;
}

void Camel::color_selector()
{

    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        qDebug() << "Color Choosen : " << color.name();
    }
}

void Camel::PrintMatrix()
{
    if (SequenceVect.isEmpty() )
        qDebug() << "Vector is Empty" ;

    for ( int indRow = 0; indRow < SequenceVect.size()  ; ++indRow )
//        for ( int indCol = 0; indCol <MatrixVector[indRow].size() ; ++indCol )
        {
            qDebug() << SequenceVect[indRow][0] << SequenceVect[indRow][1]
                     << SequenceVect[indRow][2]  << SequenceVect[indRow][3]
                    << SequenceVect[indRow][4]  << SequenceVect[indRow][5]
                    << SequenceVect[indRow][6]  << SequenceVect[indRow][7] ;
        }

}
