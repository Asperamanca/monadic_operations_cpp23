#include "defaultmonad.h"
#include "../common/printutils.h"
#include <utility>

static CSettingsMockup sg_SettingsMockup;

std::optional<ELanguage> getLanguageFromCommandLine()
{
    return sg_SettingsMockup.m_CommandLineLanguage;
}

std::optional<ELanguage> getLanguageFromRegistry()
{
    return sg_SettingsMockup.m_RegistryLineLanguage;
}

std::optional<ELanguage> getLanguageFromEnvironment()
{
    return sg_SettingsMockup.m_EnvironmentLineLanguage;
}

ELanguage getStartupLanguage()
{
    return getLanguageFromCommandLine()
            .or_else(getLanguageFromRegistry)
            .or_else(getLanguageFromEnvironment)
            .value_or(ELanguage::English);
}

void testGetStartupLanguage()
{
    // Run into fallback
    {
        sg_SettingsMockup = {};
        printlnWrapper("Fallback language: {:}",std::to_underlying(getStartupLanguage()));
        // 0 = English
    }

    // Language defined everywhere
    {
        sg_SettingsMockup = {.m_CommandLineLanguage = ELanguage::Bengali,
                             .m_RegistryLineLanguage = ELanguage::French,
                             .m_EnvironmentLineLanguage = ELanguage::Portugese};
        printlnWrapper("All sources defined: {:}",std::to_underlying(getStartupLanguage()));
        // 6 = Bengali - command line wins
    }

    // Only environment defined
    {
        sg_SettingsMockup = {.m_CommandLineLanguage = std::nullopt,
                             .m_RegistryLineLanguage = std::nullopt,
                             .m_EnvironmentLineLanguage = ELanguage::Portugese};
        printlnWrapper("Only environment defined: {:}",std::to_underlying(getStartupLanguage()));
        // 7 = Portugese - only environment is available
    }
}
