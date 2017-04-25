#include <camel.h>
#include <QDebug>

#include <QSettings>
#include "configurationmanager.h"
#include "projectmatrix.h"

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager::~ConfigurationManager()
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

bool ConfigurationManager::SaveToFile(const QString InifileName, const QString MtxName,const quint16 MtxCols,const quint16 MtxRows,const quint32 MtxColorsDepth)
{
    QSettings settings( InifileName, QSettings::IniFormat )             ;
    settings.beginGroup("Matrix_Configuration")    ;
        settings.setValue( "Name" , QString( MtxName) );
        settings.setValue( "Cols" , MtxCols ) ;
        settings.setValue( "Rows" , MtxRows ) ;
        settings.setValue( "Colors" , MtxColorsDepth ) ;
    settings.endGroup()                                                        ;

    return true ;
}
