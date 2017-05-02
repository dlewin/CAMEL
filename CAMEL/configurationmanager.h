#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H
#include "camel.h"

class ConfigurationManager
{
public:
    ConfigurationManager();
    ~ConfigurationManager();
    bool LoadFromFile(QString InifileName);
    bool SaveToFile(const QString InifileName , quint16 Rows, quint16 Cols);
};

#endif // CONFIGURATIONMANAGER_H
