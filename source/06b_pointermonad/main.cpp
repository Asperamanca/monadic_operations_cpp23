#include "pointermonad.h"

// Navigate a pointer-based tree structure to find a sibling by key
// Call multiple function that return pointers, every one of them must be checked
// Implementation using a custom pointer monad
// CPointerMonad::getSiblingValueSquared is the core usage function of this example
// class CPtr implements the monad
// Compare to 06a_PointerClassic
int main(int argc, char* argv[])
{
    // CPointerMonad::testObjectValid();
    CPointerMonad::testNodeSiblingValueSquared();
    return 0;
}
