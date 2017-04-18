#include <camel.h>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include "configurationmanager.h"
#include "projectmatrix.h"

ConfigurationManager::ConfigurationManager()
{

}

bool ConfigurationManager::LoadFromFile(QString InifileName)
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
        QString Cur_Value                                          ;
        foreach (const QString &childKey, childKeys)
        {
            Cur_Value =  settings.value(childKey).toString()                      ;
        }
    }
    settings.endGroup()                                                        ;

 return true ;
}

bool ConfigurationManager::SaveToFile(const QString InifileName)
{
    QSettings settings( InifileName, QSettings::IniFormat )             ;
    settings.beginGroup("Matrix_Configuration")    ;
   ///FIXME Need to be declared from ProjectMatrix to access MathMatrix
   ///         settings.setValue( "Name" , QString( ProjectMatrix::Name) );
   ///         settings.setValue( "Cols" , MathMatrix::Cols ) ;
   ///         settings.setValue( "Rows" , MathMatrix::Rows ) ;
   ///         settings.setValue( "Colors" , MathMatrix::Colors ) ;

    settings.endGroup()                                                        ;

    return true ;
}
