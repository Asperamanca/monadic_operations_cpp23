cmake_minimum_required(VERSION 3.14)

project(09_ExpectedMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(09_ExpectedMonad
  main.cpp
  expectedmonad.h expectedmonad.cpp
  ../common/elementdata.h ../common/elementdata.cpp
  ../common/utils.h ../common/utils.cpp
  ../common/globals.h
  ../common/stacktraceutils.h
  ../common/stacktraceutils.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
)

include(GNUInstallDirs)
install(TARGETS 09_ExpectedMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
