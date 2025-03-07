# Source code
## Download sources vs. Compiler Explorer Links
You can download the sources and build them locally. Or you can follow the compiler explorer links to single examples.
Here are the main differences:
- The compiler explorer version needs very new compilers to work. For the downloadable source package, I put in some effort so they would run (with some limitations) on compilers that are a few years old.
- On compiler explorer, every example is in a single file. This includes the actual example, but all the utilities and helper code to make it work. By comparison, the source packages are better structured, and use shared files where that makes sense
## Build and run locally
Just download the "source" folder and open CMakeLists.txt in a cmake-capable IDE of your choice.
Some features will only work with pretty new compilers (where necessary, I coded workarounds for older compilers).
Two examples (Continuation, Continuation & Writer) will only work if you have Qt 6 installed, they will simply not show if you don't have it.
### Compiler versions tested:
- GCC 13 (tested via MinGW)
- GCC 14
- Clang 17
- Clang 18
- MSVC 19.40 (VS 2022)
### Minimum compiler version required:
- GCC 13
- Clang 17
- MSVC 19.33
### Notes
Use of stacktrace is hard-disabled for GCC in downloadable sources. The feature test macro __cpp_lib_stacktrace will report support for stacktrace in GCC, but linking will fail unless you specify -lstdc++exp.
If you want to enable stacktrace for GCC, remove the protective #ifndef __GNUC__ in compilerinfo.h
## Compiler explorer links
As mentioned above, each example only consists of one file. For that reason, it's typically good to start reading the example from the bottom (main function).
The code compiler explorer does not support all compilers:
- clang cannot handle some examples due to lack of stacktrace support
- GCC 14 works, but needs a special linker flag (-lstdc++exp)
- Reasonably new version of MSVC also work

In any case, you need to set C++23 as standard version if you want to add compilers.
If you need more portable code, take a look at the downloadable sources
### Main talk examples
- Errorhandling with Exceptions (briefly shown in introduction) [https://godbolt.org/z/EMPj9nYW5](https://godbolt.org/z/EMPj9nYW5)
- Functor introduction: "Calculate & format area" example - Classic, Hand-written functors and std::ranges::views version: [https://godbolt.org/z/9er1Yq9or](https://godbolt.org/z/9er1Yq9or)
- Callables and how to pass them (includes a lot more than the slides): [https://godbolt.org/z/bcEYGYcK3](https://godbolt.org/z/bcEYGYcK3)
- Ranges/View Monad: Classic loop version of "Compile and print diagnostics" example: [https://godbolt.org/z/vbqrTWTeT](https://godbolt.org/z/vbqrTWTeT)
- Ranges/View Monad: Ranges monad version of "Compile and print diagnostics" example: [https://godbolt.org/z/W5dqnavYc](https://godbolt.org/z/W5dqnavYc)
- Pure functions: "getMultipliedView" example: [https://godbolt.org/z/9xbaY6hGe](https://godbolt.org/z/9xbaY6hGe)
- Handling Failure: Classic implementation of "Is numeric table cell value negative": [https://godbolt.org/z/fa11WMbdP](https://godbolt.org/z/fa11WMbdP)
- Handling Failure: std::optional version (Maybe monad) of "Is numeric table cell value negative": [https://godbolt.org/z/rfW6EM68b](https://godbolt.org/z/rfW6EM68b)
- Handling Failure: std::expected version of "Is numeric table cell value negative": [https://godbolt.org/z/sKGb6qPo9](https://godbolt.org/z/sKGb6qPo9)
- "Determine startup language" example (Default "monad") - std::optional::or_else: [https://godbolt.org/z/zz5coz13T](https://godbolt.org/z/zz5coz13T)
- Handling Failure: Classic implementation with pointers of "Is numeric table cell value negative": [https://godbolt.org/z/r6vYWrcfx](https://godbolt.org/z/r6vYWrcfx)
- Handling Failure: Custom pointer monad version of "Is numeric table cell value negative": [https://godbolt.org/z/hK1oxG8Tx](https://godbolt.org/z/hK1oxG8Tx)
- Continuation Monad: "Calculate & format area" (but reeeeaaaly slow): [https://godbolt.org/z/33aaco98c](https://godbolt.org/z/33aaco98c)
- Writer Monad: "Calculate & format area": [https://godbolt.org/z/r437Ea7bj](https://godbolt.org/z/r437Ea7bj)
- Combine Continuation & Writer Monads: "Calculate & format area" (but reeeeaaaly slow): [https://godbolt.org/z/hbEaWjxj7](https://godbolt.org/z/hbEaWjxj7)
- Extra (not in slides): Trace constructor / destructor calls when using "classic function" interface (with out& parameter) [https://godbolt.org/z/Psa6svY1a](https://godbolt.org/z/Psa6svY1a)
- Extra (not in slides): Trace constructor / destructor calls when just returning results [https://godbolt.org/z/9W3b9Y815](https://godbolt.org/z/9W3b9Y815)
- Extra (not in slides): Why you need perfect forwarding, and what it does: [https://godbolt.org/z/dWMjvofz9](https://godbolt.org/z/dWMjvofz9)
