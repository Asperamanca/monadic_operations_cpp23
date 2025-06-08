cmake_minimum_required(VERSION 3.14)

project(x3_BenchmarkRanges LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if (MSVC)
#     # warning level 4
#     add_compile_options(/Ob2)
# endif()

add_executable(x3_BenchmarkRanges
  main_ranges.cpp
  ctrack.hpp
  rangesutilities.h rangesutilities.cpp
  benchmarkranges.h benchmarkranges.cpp
  benchmark.h
  simulatework.h
  simulatework.cpp
  configureranges.h
  parsecommandline.h parsecommandline.cpp
)

add_executable(x3_BenchmarkErrorHandling
  main_errorhandling.cpp
  ctrack.hpp
  benchmarkerrorhandling.h benchmarkerrorhandling.cpp
  errorhandlingutilities.h
  benchmark.h
  simulatework.h
  simulatework.cpp
  configureerrorhandling.h
  parsecommandline.h parsecommandline.cpp
)

include(GNUInstallDirs)
install(TARGETS x3_BenchmarkRanges
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS x3_BenchmarkErrorHandling
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
