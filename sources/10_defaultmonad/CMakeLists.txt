cmake_minimum_required(VERSION 3.14)

project(10_DefaultMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(10_DefaultMonad
  main.cpp
  defaultmonad.h defaultmonad.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
)

include(GNUInstallDirs)
install(TARGETS 10_DefaultMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
