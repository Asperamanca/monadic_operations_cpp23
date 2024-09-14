cmake_minimum_required(VERSION 3.14)

project(04x_ClassicErrorhandlingExceptions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(04x_ClassicErrorhandlingExceptions
  main.cpp
  classicerrorhandling_exceptions.h classicerrorhandling_exceptions.cpp
  ../common/elementdata.h ../common/elementdata.cpp
  ../common/utils.h ../common/utils.cpp
  ../common/globals.h
  ../common/stacktraceutils.h
  ../common/stacktraceutils.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
)

include(GNUInstallDirs)
install(TARGETS 04x_ClassicErrorhandlingExceptions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
