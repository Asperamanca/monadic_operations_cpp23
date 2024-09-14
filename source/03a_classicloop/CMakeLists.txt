cmake_minimum_required(VERSION 3.14)

project(03a_ClassicLoop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(03a_ClassicLoop
  main.cpp
  classicloop.h classicloop.cpp
  ../common/diagnosticinfo.h
  ../common/diagnosticinfo.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  ../common/noisy.h ../common/noisy.cpp
)

include(GNUInstallDirs)
install(TARGETS 03a_ClassicLoop
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
