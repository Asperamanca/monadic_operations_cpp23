#include "defaultmonad.h"

// Get an application startup language in one of multiple different ways
// First function that succeeds defines the language
// Using std::optional's or_else
// getStartupLanguage is the core function of this example
int main(int argc, char* argv[])
{
    testGetStartupLanguage();
    return 0;
}
