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

    return OnLoad(m_parser);
}