#ifndef TESTFUNCTOR_H
#define TESTFUNCTOR_H

#include <vector>
#include <string>

namespace mop
{


// Functions to showcase various cases:
// ('SingleValue' vs. 'Vector' are the cases from the slides)


// Test functions (entry points from main):
//...first: Classic implementations
void intro01ClassicSingleValue();
void intro02ClassicVector();
void intro03ClassicOptionalValue();

//...second: Functor implementation using a function
void intro11FunctorLiftSingleValue();
void intro12FunctorLiftVector();
void intro13FunctorLiftOptionalValue();

//...third: Functor implementation using an object wrapper
void intro21FunctorWrapperSingleValue();
void intro22FunctorWrapperVector();
void intro23FunctorWrapperOptionalValue();

//...third: Using a templated functor
void intro31FunctorTemplateSingleValue();
void intro32FunctorTemplateVector();
void intro33FunctorTemplateOptionalValue();

// Showcases how a functor reflects composition
void intro41FunctorShowComposition();
// Showcases how a functor preserves identity
void intro42FunctorShowIdentity();

void introRanges01Classic();
void introRanges02FunctorView();
void introRanges03FunctorViewWithPipe();
std::vector<std::string> introRanges05ConvertViewResultToContainer();

// Extra: Shows how to produce a dangling reference
void extra1_DanglingReference();

} // namespace mop

#endif // TESTFUNCTOR_H
