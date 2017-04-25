#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H
#include "camel.h"

class ConfigurationManager
{
public:
    ConfigurationManager();
    ~ConfigurationManager();
    bool LoadFromFile(QString InifileName);
    bool SaveToFile(const QString InifileName , const QString MtxName, const quint16 MtxCols, const quint16 MtxRows, const quint32 MtxColorsDepth);
};

#endif // CONFIGURATIONMANAGER_H
