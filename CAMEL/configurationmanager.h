#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H
#include "camel.h"

class ConfigurationManager
{
public:
    ConfigurationManager();
    ~ConfigurationManager();
    bool LoadFromFile(QString InifileName);
    bool SaveToFile(const QString InifileName , QString Matrix_Declaration);
};

#endif // CONFIGURATIONMANAGER_H
