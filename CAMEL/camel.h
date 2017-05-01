#ifndef CAMEL_H
#define CAMEL_H

#include <QString>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include <QToolBar>

#include "projectmatrix.h"

namespace Ui {
class Camel;
}

class Camel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Camel(QWidget *parent = 0);
    ~Camel();
    void CreateDock();

private:
    Ui::Camel *ui;
    bool init();
    void createActions();
    void createStatusBar();
    void createDockWindows();

    QListWidget *customerList;
};

#endif // CAMEL_H
