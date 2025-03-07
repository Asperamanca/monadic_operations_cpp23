#include "defaultmonad.h"
#include "../common/printutils.h"
#include <utility>

namespace mop
{

// Mockup simulating command line, registry and environment variable
//  This allows me to construct various test cases
//  Non-optimal solution, because e.g. unit tests might interfere with one another through this global
//  (But simplicity was more important here)
static CSettingsMockupOpt sg_SettingsMockupOpt;


ELanguage getStartupLanguageOpt()
{
    return getLanguageFromCommandLineOpt()
            .or_else(getLanguageFromRegistryOpt)
            .or_else(getLanguageFromEnvironmentOpt)
            .value_or(ELanguage::English);
}


void testGetStartupLanguageOpt()
{
    // Run into fallback
    {
        sg_SettingsMockupOpt = {};
        printlnWrapper("Fallback language: {:}",std::to_underlying(getStartupLanguageOpt()));
        // 0 = English
    }

    // Language defined everywhere
    {
        sg_SettingsMockupOpt = {.m_oCommandLineLanguage = ELanguage::Bengali,
                             .m_oRegistryLineLanguage = ELanguage::French,
                             .m_oEnvironmentLineLanguage = ELanguage::Portugese};
        printlnWrapper("All sources defined: {:}",std::to_underlying(getStartupLanguageOpt()));
        // 6 = Bengali - command line wins
    }

    // Only environment defined
    {
        sg_SettingsMockupOpt = {.m_oCommandLineLanguage = std::nullopt,
                             .m_oRegistryLineLanguage = std::nullopt,
                             .m_oEnvironmentLineLanguage = ELanguage::Portugese};
        printlnWrapper("Only environment defined: {:}",std::to_underlying(getStartupLanguageOpt()));
        // 7 = Portugese - only environment is available
    }
}


std::optional<ELanguage> getLanguageFromCommandLineOpt()
{
    return sg_SettingsMockupOpt.m_oCommandLineLanguage;
}

std::optional<ELanguage> getLanguageFromRegistryOpt()
{
    return sg_SettingsMockupOpt.m_oRegistryLineLanguage;
}

std::optional<ELanguage> getLanguageFromEnvironmentOpt()
{
    return sg_SettingsMockupOpt.m_oEnvironmentLineLanguage;
}



} // namespace mop

