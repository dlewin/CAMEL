#ifndef CAMEL_H
#define CAMEL_H

#include <QString>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include <QToolBar>

#include "guimatrix.h"

struct Matrix_Model
{
    QString Name ;
    QString Description ;
    quint16 Rows ;
    quint16 Cols ;
    quint32 ColorsDepth ;
    QVector< QPair<QString, QRgb> > ColorsList ;
};


namespace Ui {
class Camel;
}

class Camel : public QMainWindow
{
    Q_OBJECT
private:    

    QWidget *MatrixGui ;
    QListWidget *SequenceList ;
    void MatrixSnapshot(QImage &imageTest, uint BtnID, QRgb BtnCol);
    void PrintMatrix();
    void CreateDock();
    bool LoadConfig() ;
    bool SaveConfig(const QString InifileName , quint16 Rows, quint16 Cols);
    int SaveSequence(QString Filename, QVector<QVector<QRgb> > &MatrixVector);
    int LoadSequence(QString Filename, QVector<QVector<QRgb> > &MatrixVector);
    uint MatxRows, MatxCols ;
    GuiMatrix* CurrentGUIMatrix ;
    QVector< QPair<QString, QRgb> > ColorsL ;
    QVector<QVector<QRgb>> SequenceVect;
    QVector<Matrix_Model> MatrixModels ;
    QAction* SelectColors_Action;
    QAction*  SaveGUIPattern_Action ;
    QAction*  LoadFile_Action ;
    QAction* Wizard_Action;
    Ui::Camel *ui;


public:
    explicit Camel(QWidget *parent = 0);
    ~Camel();


private slots:
    void color_selector();
    int Wizard();
    void PushGUIPattern_ToSequence();
    void onListRightClicked() ;
    void eraseItem();
    void addItem() ;
    void ClearList() ;
    void showContextMenu(const QPoint &pos) ;
    void LoadingConfig();
};

#endif // CAMEL_H
