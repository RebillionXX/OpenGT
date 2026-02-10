#pragma once
#include "Util/TextParser.h"

class CConfigBase
{
protected:
    struct ConfigEntry
    {
        std::string m_key;
        std::vector<std::string> m_values;
    };

protected:
    // Full path to the configuration file
    std::string m_filePath;

    // Text parser used to read and interpret the configuration file
    CTextParser m_parser;

protected:
    // Called after file is loaded
    virtual bool OnLoad(const std::vector<ConfigEntry>& entries) = 0;
    virtual bool OnReload() = 0; // Irrelevant

public:
    CConfigBase();
    virtual ~CConfigBase();

    // Loads configuration data from the specified file path
    // Returns: true if the file was successfully loaded and parsed
    bool Load(const std::string& filePath);
};