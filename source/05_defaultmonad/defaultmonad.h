#ifndef DEFAULTMONAD_H
#define DEFAULTMONAD_H

#include <optional>

enum class ELanguage : int
{
    English = 0,
    StandardChinese = 1,
    Hindi = 2,
    Spanish = 3,
    Arabic = 4,
    French = 5,
    Bengali = 6,
    Portugese = 7,
};

struct CSettingsMockup
{
    std::optional<ELanguage> m_CommandLineLanguage{};
    std::optional<ELanguage> m_RegistryLineLanguage{};
    std::optional<ELanguage> m_EnvironmentLineLanguage{};
};


std::optional<ELanguage> getLanguageFromCommandLine(/*...cmdline params...*/);
std::optional<ELanguage> getLanguageFromRegistry();
std::optional<ELanguage> getLanguageFromEnvironment();


ELanguage getStartupLanguage();


void testGetStartupLanguage();


#endif // DEFAULTMONAD_H
