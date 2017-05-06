#ifndef CAMEL_H
#define CAMEL_H

#include <QString>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include <QToolBar>

#include "guimatrix.h"
#include "projectmatrix.h"


struct Matrix_Model
{
    QString Name ;
    QString Description ;
    quint16 Rows ;
    quint16 Cols ;
    quint32 ColorsDepth ;
    QVector< QPair<QString, QColor> > ColorsList ;
};


namespace Ui {
class Camel;
}

class Camel : public QMainWindow
{
    Q_OBJECT
private:
    QVector<Matrix_Model> MatrixModels ;
    QAction* SelectColors_Action;
    QAction* Wizard_Action;
    Ui::Camel *ui;
    void CreateDock();
    bool LoadFromFile(QString InifileName) ;
    bool SaveToFile(const QString InifileName , quint16 Rows, quint16 Cols);

public:
    ProjectMatrix* workMatrix ;
    explicit Camel(QWidget *parent = 0);
    ~Camel();

private slots:
    void color_selector();
    int Wizard();
};

#endif // CAMEL_H
