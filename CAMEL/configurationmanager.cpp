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

/* Models section is where each model, ie: the physical leds matrix, is described
 a model is :

    [Models]
    name = rowsxcolsxcolors

 Sequence section is the container of the patterns Sequence
 Each sequence must have at least :

    [SequenceName]
    Patterns=Patterns1.bin
    Compatibility=8x8@3
    1=Pattern1

 and eventually:
    2=tempo500
    3=Pattern3
    ....
*/
///TODO change the Matrix_Declaration for colors
bool ConfigurationManager::SaveToFile(const QString InifileName, QString Matrix_Declaration)
{
    QSettings settings( InifileName, QSettings::IniFormat )                     ;
    settings.beginGroup("Models")                                                       ;
        settings.setValue( "Adafruit_BicolorLEDSquarePixel" , Matrix_Declaration )        ;
        settings.setValue("Adafruit_BicolorLEDSquarePixel/Red","1");
        settings.setValue("Adafruit_BicolorLEDSquarePixel/Green","1");
        settings.setValue("Adafruit_BicolorLEDSquarePixel/Blued","0");
        settings.setValue( "SenseHat" , Matrix_Declaration )        ;
        settings.setValue("SenseHat/Red","255");
        settings.setValue("SenseHat/Green","255");
        settings.setValue("SenseHat/Blued","255");
    settings.endGroup()                                                        ;
    settings.beginGroup("Sequence1")                                               ;
        settings.setValue( "File" , "Pattern1.bin" ) ;
        settings.setValue( "Cols" , "8x8@3" ) ;
        settings.setValue ( "1","Pattern1" ) ;
    settings.endGroup()                                                        ;

    return true ;
}
