#include "camel.h"
#include "ui_camel.h"

Camel::Camel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camel)
{
    ui->setupUi(this);
}

Camel::~Camel()
{
    delete ui;
}
