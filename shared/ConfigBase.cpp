#include "ConfigBase.h"

CConfigBase::CConfigBase()
{
    //
}

CConfigBase::~CConfigBase()
{
    //
}

bool CConfigBase::Load(const std::string& filePath)
{
    m_filePath = filePath;

    if (!m_parser.LoadFile(filePath))
        return false;

    // Setup Config Entries.
    std::vector<ConfigEntry> entries;

    for (i32 i = 0; i < m_parser.GetLineCount(); i++)
    {
        std::string line = m_parser.GetLine(i);
        if (line.empty() || line[0] == '#' || (line.size() > 1 && line[0] == '/' && line[1] == '/'))
            continue;

        std::vector<std::string> tokens = m_parser.TokenizeLine(i);
        if (tokens.empty() || tokens.size() <= 1)
            continue;

        ConfigEntry entry;
        entry.m_key = tokens[0];
        entry.m_values.insert(entry.m_values.end(), tokens.begin() + 1, tokens.end());

        entries.push_back(entry);
    }
    return OnLoad(entries);
}