#include "matrix.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

Matrix::Matrix(QString Name,const quint16 Cols, const quint16 Rows, const quint16 Colors)
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
    QString Temp_String;

    QSettings settings( InifileName, QSettings::IniFormat )             ;
    settings.beginGroup("Matrix_Configuration")    ;
        settings.setValue( "dimensions" , 8 ) ;
    settings.endGroup()                                                        ;
    return true ;
}




Matrix::~Matrix()
{

}
