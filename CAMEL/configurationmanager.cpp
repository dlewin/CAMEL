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
    QStringList AllKeysList ( settings.allKeys()) ;

    QStringList TempModel ;
    for (auto it: AllKeysList)
    {
         TempModel << it.split('/');

//        qDebug() << it.split('/') << " => " <<   settings.value(it).toString()              ;

    }

    QStringList ModelsList ;
     settings.beginGroup("Models");
        ModelsList << settings.childKeys() ;
     settings.endGroup();

     for (auto it2: ModelsList)
     {
         qDebug()<< "Model:" << it2 << "Title:" << settings.value(it2).toString();

         settings.beginGroup(it2);
//            qDebug() << it2 << "-" <<settings.allKeys() ;
            for (auto iter :settings.allKeys() )
            {
               QString pipo= iter ;
               if (pipo.contains("Colors/"))
                   qDebug()<< "Colors: " <<  pipo.remove(QRegExp("Colors/")) << "=" << settings.value(iter).toString() ;
               else
                    qDebug() << iter << "=>" <<settings.value(iter).toString()  ;
            }

         settings.endGroup();
     }


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
bool ConfigurationManager::SaveToFile(const QString InifileName, quint16 Rows ,quint16 Cols  )
{
    QSettings settings( InifileName, QSettings::IniFormat )                     ;
    settings.beginGroup("Models")                                                       ;
        settings.setValue( "Adafruit_BicolorLEDSquarePixel" , "2 Colors Leds Matrix" )        ;
        settings.setValue( "SenseHat" , "The SenseHat" )        ;
    settings.endGroup()                                                        ;
    settings.beginGroup("Adafruit_BicolorLEDSquarePixel") ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors/Red", "0x800000");
        settings.setValue( "Colors/Green","0x008000");
        settings.setValue( "Colors/Orange","0xffa500");
    settings.endGroup()                                                        ;
    settings.beginGroup("SenseHat") ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors","0xFFFFFF");
    settings.endGroup()  ;
    settings.beginGroup("Sequence1")                                               ;
        settings.setValue( "File" , "Pattern1.bin" ) ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors","0x000003");
        settings.setValue ( "1","Pattern1" ) ;
    settings.endGroup()                                                        ;

    return true ;
}
