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
    int Rows=8,Cols=8, ColorDepth=3 ; //Debug: will be provided by the wizard
    GuiMatrix* Matrix_8x8x3 = new GuiMatrix(Rows,Cols,ColorDepth,MatrixGui );

    setCentralWidget(MatrixGui);

//    ProjectMatrix workMatrix("Adafruit Bicolors I2C Leds Matrix", 8,8,3);
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
    dockWidget3->setWidget(new QPushButton );
    dockWidget3->setAllowedAreas(Qt::RightDockWidgetArea) ;
    addDockWidget(Qt::RightDockWidgetArea, dockWidget3);

    QPixmap matrix(":/matrix_icon");
    QPixmap wizard(":/wizard");
    QPixmap magic(":/magic");
    QPixmap colors(":/colors");

    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->addAction(QIcon(matrix), "test");
    toolbar->addAction(QIcon(wizard), "New Matrix");
    toolbar->addAction(QIcon(magic), "New Matrix");
     SelectColors_Action =toolbar->addAction (QIcon(colors), "Select color");

     connect(SelectColors_Action, SIGNAL(triggered()), this, SLOT(color_selector() ));
}

void Camel::color_selector()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        qDebug() << "Color Choosen : " << color.name();
    }
}
