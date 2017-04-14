#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

Matrix::Matrix(QString Name,const quint16 Cols, const quint16 Rows, const quint16 Colors)
{
 //Rien
       QString pipo;
}

bool Matrix::LoadFromFile(QFile Filename)
{

    QFile Inifile("Camel.ini")   ;
    // Checks if the ini file exists
    if ( !Inifile.exists() )
    {
        qDebug() << "The file" << Inifile.fileName() << "does not exist.";
        return false;
    }

    QSettings settings( "FileCleaner.ini", QSettings::IniFormat )             ;


    settings.beginGroup( "Filters" )                                          ;        // Reading the filters section
    {
        QStringList childKeys = settings.childKeys()                            ;
        QString Cur_Value, Type_Letter                                          ;
        foreach (const QString &childKey, childKeys)
        {
            Cur_Value =  settings.value(childKey).toString()                      ;
        }
    }
    settings.endGroup()                                                        ;

 return true ;
}

bool Matrix::SaveToFile(const QFile Filename)
{
    QString Temp_String;

    QFile Inifile("Camel.ini")   ;
    // Checks if the ini file exists

    QSettings settings( "Camel.ini", QSettings::IniFormat )             ;
    settings.setValue( "Expr_Type + Key_index ", Temp_String ) ;

    return true ;
}




Matrix::~Matrix()
{

}
