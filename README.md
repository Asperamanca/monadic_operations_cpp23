# Safe and Readable Code: Monadic Operations in C++23
## Just download everything
[ZIP](https://github.com/Asperamanca/monadic_operations_cpp23/archive/refs/heads/main.zip)
## Slides
[PDF](MonadicOperationsInCpp23.pdf)
## Code examples
[Source code page](sources/README.md)

[Get me to the compiler explorer links](sources/README.md#compiler-explorer-links)
## References by Topic
### Functional and Declarative Programming (General and Theory)
- Book: [Functional Programming in C++, by Ivan Čukić](https://www.manning.com/books/functional-programming-in-c-plus-plus?a_aid=FPinCXX&a_bid=441f12cc)
     * My primer for functional programming. A bit dated (targets C++17), but explains a lot of functional concepts in an understandable way
- Book: [Category Theory for Programmers, by Bartosz Milewski](https://bartoszmilewski.com/2014/10/28/category-theory-for-programmers-the-preface/)
- Video: [Category Theory for Programmers, by Bartosz Milewski](https://www.youtube.com/watch?v=I8LbkfSSR58)
     * My talk is light on theory, this is the opposite. Where I tried to stay close to conventional programming patterns, while adding some functional paradigms, this beams you to an alien planet. Appears to be very thorough and in general well-explained.
- Video: [Functional C++ - Gašper Ažman - C++Now 2024](https://www.youtube.com/watch?v=bHxvfwTnJhg)
     * Presents a library that brings the usage of monads in C++ to new levels. Type-checked multi-dispatch with compile-time errors. Monads of monads. Goes far beyond my talk, both in depth and speed
- Video: [Ben Deane “Easy to Use, Hard to Misuse: Declarative Style in C++”](https://www.youtube.com/watch?v=2ouxETt75R4)
     * Covers a much wider scope: Why should we strive for a more declarative coding style, and how can we achieve it in C++? With interesting excursions into the history of the language. Well researched, though slightly dated (from 2018).
- Video: ['Declarative Thinking, Declarative Practice' - Kevlin Henney](https://www.youtube.com/watch?v=nrVIlhtoE3Y)
     * Mostly motivational talk why you should write more declarative code (and also how), not specific for C++. Entertaining.
- Video: [Monads in Modern C++ - Georgi Koyrushki & Alistair Fisher](https://www.youtube.com/watch?v=cE_YaFMhTK8)
     * The inspiration for my own talk. Covers similar ground, but explains things a bit differently. Which one is better? Your call!
### Monads specifically
- Article: [Using Monads in C++ to Solve Constraints (Part 1 of a 4-part series)](https://bartoszmilewski.com/2015/05/11/using-monads-in-c-to-solve-constraints-1-the-list-monad/)
     * Explains in detail how to combine two monads to solve a non-trivial puzzle, and highlights the benefits of the solution. Weaves in a lot of theoretical background.
- Article: [You probably wrote half a monad by accident](https://gieseanw.wordpress.com/2024/06/25/you-probably-wrote-half-a-monad-by-accident/)
     * Short and entertaining, yet educational
- Code sample: [Monads/Writer monad](https://rosettacode.org/wiki/Monads/Writer_monad)
     * Brief explanation of the writer monad, with example implementations in different languages
### Ranges and Views
- Video: [Effective Ranges: A Tutorial for Using C++2x Ranges - Jeff Garland](https://www.youtube.com/watch?v=QoaVRQvA6hI)
     * So far my best primer if you want to use std::ranges
- Video: [Understanding the Filter View to Use it Right](https://www.youtube.com/watch?v=jR3WE-hAhCc)
     * std::views::filter has lots of traps built-in. This talk helps you understand and avoid them.
- Video: [Rappel: Compose Algorithms, Not Iterators - Google's Alternative to Ranges](https://www.youtube.com/watch?v=itnyR9j8y6E)
     * Presents a library that utilizes an alternative approach to std::ranges. Since the library is not open-sourced (as of writing), the most important takeaway is the motivation not to use ranges in the first place, and that's quite interesting.
- Paper: [The One Ranges Proposal (P0896)](https://wg21.link/P0896R4)
### Optional and Expected
- Article: [How to Use Monadic Operations for `std::optional` in C++23](https://www.cppstories.com/2023/monadic-optional-ops-cpp23/)
     * Blog post explaining the monadic interface of std::optional in C++23. If you'd like to read another explanation about that, this is a good place to start.
- Article: [The definite guide to std::expected](https://johnfarrier.com/the-definitive-guide-to-std-expected-in-c/)
     * Why use std::expected, and lots of examples on how to use it
- Video: [The expected outcome, by Ivan Čukić](https://youtu.be/1O_t7rxuq0c)
     * About error handling, and std::expected in particular.
- Paper: [Monadic operations for std::optional (P0798)](https://wg21.link/P0798R8)
- Paper: [std::expected (P0323)](https://wg21.link/P0323R12)
- Paper: [Monadic operations for std::expected (P2505)](https://wg21.link/P2505R5)
- Paper: [Give std::optional Range Support (P3168)](https://wg21.link/P3168R2)
 ### Continuations & Concurrency
 - Article: [Asynchronous APIs in Qt 6](https://www.qt.io/blog/asynchronous-apis-in-qt-6)
     * Explains monadic operations on QtConcurrent
- Article: [Design and evolution of C++ future continuations](https://ikriv.com/blog/?p=4916)
     * About the many attempts to make continuation available in C++. There seems to be a really good chance that P2300 mentioned in the article makes it into C++26.
- Paper: [std::execution: sender-receiver model of execution control (P2300)](https://wg21.link/P2300R10)
 ### Other C++23 Features
- Article: [C++23: The stacktrace library](https://www.sandordargo.com/blog/2022/09/21/cpp23-stacktrace-library)
     * More about std::stacktrace
- Article: [std::print in C++23](https://vitaut.net/posts/2023/print-in-cpp23/)
     * Compact article on std::print, and why you might want to prefer it to printf and iostream.
- Video: [C++23: An Overview of Almost All New and Updated Features - Marc Gregoire](https://www.youtube.com/watch?v=Cttb8vMuq-Y)
     * Overview over C++23, really goes through the list and explains every feature briefly
- Video: [Advanced Usage of the C++23 Stacktrace Library - James Pascoe](https://www.youtube.com/watch?v=rynny8wP3M4)
     * Usage of the C++23 stacktrace library, explained in just over 20 minutes
- Paper: [A Proposal to add stacktrace library (P0881)](https://wg21.link/P0881R7)
- Paper: [Formatted output (P2093)](https://wg21.link/P2093R14)
- Paper: [Text Formatting (P0645)](https://wg21.link/P0645R10)
### Compiler support
- [C++23 Compiler Support](https://en.cppreference.com/w/cpp/compiler_support/23)
## Replacement libraries
You want to use some of the features I presented, but do not have a new enough compiler and/or standard version?
There are libraries you can use as replacement.

*Disclaimer: I don't have first-hand experience with them. Please evaluate whether they fit your use case, and whether they are still actively maintained before using*
- [Ranges v3](https://github.com/ericniebler/range-v3): The library gave the direction for the standardization of ranges, and surpasses C++23 ranges in some functionality
- [Sy Brand's expected library](https://github.com/TartanLlama/expected): "By far the most popular implementation is Sy Brand’s, with over 500 stars on GitHub and extensive usage." (Quote from [P0323R10 - std::expected](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0323r10.html#%F0%9F%92%9C))
- [Boost optional](https://www.boost.org/doc/libs/1_86_0/libs/optional/doc/html/index.html): Optional with a monadic interface (look for "map" instead of "and_then", and it's partially missing in the docs)
- [STX: C++17 & C++ 20 error-handling and utility extensions](https://github.com/lamarrr/STX): Contains an 'optional' and 'expected' implementation with monadic operations

