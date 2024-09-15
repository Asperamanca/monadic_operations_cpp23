#ifndef TESTFUNCTOR_H
#define TESTFUNCTOR_H

#include <vector>
#include <string>

void test01_DoublePowToStrClassic();
void test02_DoublePowToStrClassicWithFunctions();
void test03_DoublePowToStrFunctorView();
void test04_DoublePowToStrFunctorViewWithPipe();
std::vector<std::string> test05_convertViewResultToContainer();

// Extra: Eager ranges algorithm
void extra1_FunctorVectorDoublePowToStr();

// Extra: Shows how to produce a dangling reference
void extra2_DanglingReference();

#endif // TESTFUNCTOR_H
