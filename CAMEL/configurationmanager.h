#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H
#include "camel.h"

class ConfigurationManager
{
public:
    ConfigurationManager();
    bool LoadFromFile(QString InifileName);
    bool SaveToFile(const QString InifileName );
};

#endif // CONFIGURATIONMANAGER_H
