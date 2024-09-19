# Monadic Operations in C++23 (and beyond)
## Slides
## Code examples
[Source code](source/Readme.md)
## References
### Books
- [Functional Programming in C++, by Ivan Čukić](https://www.manning.com/books/functional-programming-in-c-plus-plus?a_aid=FPinCXX&a_bid=441f12cc)
     * My primer for functional programming. A bit dated (targets C++17), but explains a lot of functional concepts in an understandable way
- [Category Theory for Programmers, by Bartosz Milewski](https://bartoszmilewski.com/2014/10/28/category-theory-for-programmers-the-preface/)
     * I have only gotten partway into it, but this looks like a gold mine if you want to learn the theory behind functional programming
### Blog posts and articles
- [Using Monads in C++ to Solve Constraints (Part 1 of a 4-part series)](https://bartoszmilewski.com/2015/05/11/using-monads-in-c-to-solve-constraints-1-the-list-monad/)
     * Explains in detail how to combine two monads to solve a non-trivial puzzle, and highlights the benefits of the solution. Weaves in a lot of theoretical background.
- [Monads in C++ ](https://bartoszmilewski.com/2011/07/11/monads-in-c/)
- [You probably wrote half a monad by accident](https://gieseanw.wordpress.com/2024/06/25/you-probably-wrote-half-a-monad-by-accident/)
     * Short and entertaining, yet educational
- [Monads/Writer monad](https://rosettacode.org/wiki/Monads/Writer_monad)
     * Brief explanation of the writer monad, with example implementations in different languages
- [How to Use Monadic Operations for `std::optional` in C++23](https://www.cppstories.com/2023/monadic-optional-ops-cpp23/)
     * Blog post explaining the monadic interface of std::optional in C++23. If you'd like to read another explanation about that, this is a good place to start.
- [C++23: The stacktrace library](https://www.sandordargo.com/blog/2022/09/21/cpp23-stacktrace-library)
     * More about std::stacktrace
- [Asynchronous APIs in Qt 6](https://www.qt.io/blog/asynchronous-apis-in-qt-6)
     * Explains monadic operations on QtConcurrent
### Videos
- [Functional C++ - Gašper Ažman - C++Now 2024](https://www.youtube.com/watch?v=bHxvfwTnJhg)
     * Presents a library that brings the usage of monads in C++ to new levels. Type-checked multi-dispatch with compile-time errors. Monads of monads. Goes far beyond my talk, both in depth and speed
- [Ben Deane “Easy to Use, Hard to Misuse: Declarative Style in C++”](https://www.youtube.com/watch?v=2ouxETt75R4)
     * Covers a much wider scope: Why should we strive for a more declarative coding style, and how can we achieve it in C++? With interesting excursions into the history of the language. Well researched, though slightly dated (from 2018).
- [Monads in Modern C++ - Georgi Koyrushki & Alistair Fisher](https://www.youtube.com/watch?v=cE_YaFMhTK8)
     * The inspiration for my own talk. Covers similar ground, but explains things a bit differently. Which one is better? Your call!
- [Effective Ranges: A Tutorial for Using C++2x Ranges - Jeff Garland](https://www.youtube.com/watch?v=QoaVRQvA6hI)
     * So far my best primer if you want to use std::ranges
- [C++23: An Overview of Almost All New and Updated Features - Marc Gregoire](https://www.youtube.com/watch?v=Cttb8vMuq-Y)
     * Overview over C++23, really goes through the list and explains every feature briefly
- ['Declarative Thinking, Declarative Practice' - Kevlin Henney](https://www.youtube.com/watch?v=nrVIlhtoE3Y)
     * Mostly motivational talk why you should write more declarative code (and also how), not specific for C++. Entertaining.
- [Understanding the Filter View to Use it Right](https://www.youtube.com/watch?v=jR3WE-hAhCc)
     * std::views::filter has lots of traps built-in. This talk helps you understand and avoid them.
- [Rappel: Compose Algorithms, Not Iterators - Google's Alternative to Ranges](https://www.youtube.com/watch?v=itnyR9j8y6E)
     * Presents a library that utilizes an alternative approach to std::ranges. Since the library is not open-sourced (as of writing), the most important takeaway is the motivation not to use ranges in the first place, and that's quite interesting.
## Papers
- [The One Ranges Proposal (P0896)](https://wg21.link/P0896R4)
- [Monadic operations for std::optional (P0798)](https://wg21.link/P0798R8)
- [std::expected (P0323)](https://wg21.link/P0323R12)
- [Monadic operations for std::expected (P2505)](https://wg21.link/P2505R5)
- [A Proposal to add stacktrace library (P0881)](https://wg21.link/P0881R7)
- [Formatted output (P2093)](https://wg21.link/P2093R14)
- [Text Formatting (P0645)](https://wg21.link/P0645R10)
- [Give std::optional Range Support (P3168)](https://wg21.link/P3168R2)
- [std::execution: sender-receiver model of execution control (P2300)](https://wg21.link/P2300R10)
## Other
- [C++23 Compiler Support](https://en.cppreference.com/w/cpp/compiler_support/23)


