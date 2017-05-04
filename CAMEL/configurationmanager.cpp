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

    QStringList ModelsList, ModelText ;
    settings.beginGroup("Models");
        {
              ModelsList << settings.childKeys()                            ;
              foreach (const QString &childKey, ModelsList)
              {
                  ModelText <<  settings.value(childKey).toString()                      ;
              }
          }
     settings.endGroup();

     qDebug() << ModelText  ;

    QVector<Matrix_Model> AllModels ;

     for (auto it2: ModelsList)
     {

         Matrix_Model Temp_Model;

         qDebug()<< "Model:" << it2 ;
         Temp_Model.Name= QString(it2) ;

         settings.beginGroup(it2);
//            qDebug() << it2 << "-" <<settings.allKeys() ;
            for (auto iter :settings.allKeys() )
            {
               QString buffer= iter ;
               if (buffer.contains("Colors/"))      // Looking for a Color List Name = Value
               {
                   QString ColorName = buffer.remove(QRegExp("Colors/"));
                   QColor ColorValue=  QColor(settings.value(iter).toInt()) ;

                Temp_Model.ColorsList << QPair<QString, QColor> ( ColorName,ColorValue ) ;
                   qDebug()<< "Colors: " <<  buffer.remove(QRegExp("Colors/")) << ".=." << settings.value(iter).toString() ;
               }
               else
               {
                   if ( buffer.contains("Cols") )
                       Temp_Model.Cols = settings.value(iter).toUInt();
                   else if ( buffer.contains("Rows") )
                        Temp_Model.Rows = settings.value(iter).toUInt() ;
                   else if ( buffer.contains("colorsdepth") )                        // Looking for a ColorDepth = Value
                        Temp_Model.ColorsDepth = settings.value(iter).toUInt() ;
//                   qDebug() << buffer << "=>" <<settings.value(iter).toString()  ;
               }
            }

         settings.endGroup();

         // We now have all the elements to create a complete model
       AllModels.push_back(Temp_Model );

     }

     for ( int i=0; i<AllModels.size(); i++)
     {
        qDebug() << AllModels[i].Name <<" / " << AllModels[i].Description <<" / "<< AllModels[i].ColorsDepth <<" / "<< AllModels[i].ColorsList <<" / ";
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
        settings.setValue( "Colors/Red", "8388608");
        settings.setValue( "Colors/Green","32768");
        settings.setValue( "Colors/Orange","16753920");
    settings.endGroup()                                                        ;
    settings.beginGroup("SenseHat") ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "colorsdepth","16777215");
    settings.endGroup()  ;
    settings.beginGroup("Sequence1")                                               ;
        settings.setValue( "File" , "Pattern1.bin" ) ;
        settings.setValue( "Rows",Rows);
        settings.setValue( "Cols", Cols);
        settings.setValue( "Colors","000003");
        settings.setValue ( "1","Pattern1" ) ;
    settings.endGroup()                                                        ;

    return true ;
}
