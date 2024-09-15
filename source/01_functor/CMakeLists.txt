cmake_minimum_required(VERSION 3.14)

project(01_Functor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(01_Functor
  main.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  testfunctor.h testfunctor.cpp
)

include(GNUInstallDirs)
install(TARGETS 01_Functor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
