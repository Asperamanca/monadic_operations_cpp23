cmake_minimum_required(VERSION 3.14)

project(07_PureFunctions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(07_PureFunctions
  main.cpp

  ../common/diagnosticinfo.h
  ../common/diagnosticinfo.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  ../common/noisy.h ../common/noisy.cpp
  purefunctions.h purefunctions.cpp
)

include(GNUInstallDirs)
install(TARGETS 07_PureFunctions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
