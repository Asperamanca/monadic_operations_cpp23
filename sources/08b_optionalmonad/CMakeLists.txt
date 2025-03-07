cmake_minimum_required(VERSION 3.14)

project(08b_OptionalMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(08b_OptionalMonad
  main.cpp
  optionalmonad.h optionalmonad.cpp
  ../common/elementdata.h ../common/elementdata.cpp
  ../common/utils.h ../common/utils.cpp
  ../common/globals.h
  ../common/compilerinfo.h
  ../common/printutils.h
  ../common/stacktraceutils.h
  ../common/stacktraceutils.cpp
  optionalmonadtest.h optionalmonadtest.cpp
)

include(GNUInstallDirs)
install(TARGETS 08b_OptionalMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
