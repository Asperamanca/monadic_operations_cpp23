cmake_minimum_required(VERSION 3.14)

project(08a_ClassicErrorhandling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(08a_ClassicErrorhandling
  main.cpp
  classicerrorhandling.h classicerrorhandling.cpp
  ../common/elementdata.h ../common/elementdata.cpp
  ../common/utils.h ../common/utils.cpp
  ../common/globals.h
  ../common/stacktraceutils.h ../common/stacktraceutils.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  legacyupgrade.h
)

include(GNUInstallDirs)
install(TARGETS 08a_ClassicErrorhandling
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
