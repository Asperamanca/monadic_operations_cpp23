cmake_minimum_required(VERSION 3.14)

project(04_Callables LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(04_Callables
  main.cpp
  testcallables.h testcallables.cpp
  ../common/sharedfunctions.h
  ../common/sharedfunctions.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
)

include(GNUInstallDirs)
install(TARGETS 04_Callables
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
