#ifndef CAMEL_H
#define CAMEL_H

#include <QString>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include <QToolBar>

#include "guimatrix.h"
#include "projectmatrix.h"


namespace Ui {
class Camel;
}

class Camel : public QMainWindow
{
    Q_OBJECT
private:
    QAction* SelectColors_Action;
    Ui::Camel *ui;
    void CreateDock();
public:
    explicit Camel(QWidget *parent = 0);
    ~Camel();

private slots:
    void color_selector();
};

#endif // CAMEL_H
