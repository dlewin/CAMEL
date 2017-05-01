#include "camel.h"
#include "ui_camel.h"

Camel::Camel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camel)
{
    ui->setupUi(this);
    setDockNestingEnabled(true);
    QWidget *widget = new QWidget;
       setCentralWidget(widget);

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
       addDockWidget(Qt::LeftDockWidgetArea, dockWidget3);
//       tabifyDockWidget(dockWidget2, dockWidget3);

QPixmap matrix(":/matrix_icon");
QPixmap wizard(":/wizard");
QPixmap magic(":/magic");
QToolBar *toolbar = addToolBar("main toolbar");
 toolbar->addAction(QIcon(matrix), "test");
  toolbar->addAction(QIcon(wizard), "New Matrix");
  toolbar->addAction(QIcon(magic), "New Matrix");

   ProjectMatrix workMatrix("Adafruit Bicolors I2C Leds Matrix", 8,8,3);
}

Camel::~Camel()
{
    delete ui;
}

void Camel::CreateDock()
{

//QDockWidget *dock = new QDockWidget(tr("Customers"), this);
//    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    customerList = new QListWidget(dock);
//    customerList->addItems(QStringList()
//            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
//            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
//            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
//            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
//            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
//            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
//    dock->setWidget(customerList);
//
}
