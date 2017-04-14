#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

Matrix::Matrix(const QString MName, const quint16 MCols, const quint16 MRows, const quint16 MColors):Name(MName),Cols(MCols),Rows(MRows),Colors( MColors)
{
}

bool Matrix::LoadFromFile(QString InifileName)
{
    QFile Inifile(InifileName) ;
    // Checks if the ini file exists
    if ( !Inifile.exists() )
    {
        qDebug() << "The file" << Inifile.fileName() << "does not exist.";
        return false;
    }

    QSettings settings( InifileName , QSettings::IniFormat )             ;


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

bool Matrix::SaveToFile(const QString InifileName)
{
    QSettings settings( InifileName, QSettings::IniFormat )             ;
    settings.beginGroup("Matrix_Configuration")    ;
        settings.setValue( "dimensions" , Cols ) ;
    settings.endGroup()                                                        ;

    return true ;
}




Matrix::~Matrix()
{

}
