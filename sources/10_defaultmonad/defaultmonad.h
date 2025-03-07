#ifndef DEFAULTMONAD_H
#define DEFAULTMONAD_H

#include <optional>

namespace mop
{


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

// Main function
ELanguage getStartupLanguageOpt();

std::optional<ELanguage> getLanguageFromCommandLineOpt(/*...cmdline params...*/);
std::optional<ELanguage> getLanguageFromRegistryOpt();
std::optional<ELanguage> getLanguageFromEnvironmentOpt();

// Main test function - shows various cases
void testGetStartupLanguageOpt();


struct CSettingsMockupOpt
{
    std::optional<ELanguage> m_oCommandLineLanguage{};
    std::optional<ELanguage> m_oRegistryLineLanguage{};
    std::optional<ELanguage> m_oEnvironmentLineLanguage{};
};




} // namespace mop

#endif // DEFAULTMONAD_H
