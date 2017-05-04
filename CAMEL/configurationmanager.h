#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H
#include "camel.h"


struct Matrix_Model
{
    QString Name ;
    QString Description ;
    quint16 Rows ;
    quint16 Cols ;
    quint32 ColorsDepth ;
    QVector<quint32> ColorsList ;
};

class ConfigurationManager
{
public:
    ConfigurationManager();
    ~ConfigurationManager();
    bool LoadFromFile(QString InifileName);
    bool SaveToFile(const QString InifileName , quint16 Rows, quint16 Cols);
};

#endif // CONFIGURATIONMANAGER_H
