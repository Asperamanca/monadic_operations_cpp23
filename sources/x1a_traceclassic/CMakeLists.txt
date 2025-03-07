cmake_minimum_required(VERSION 3.14)

project(x1a_TraceClassic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(x1a_TraceClassic
  main.cpp
  ../common/noisy.h ../common/noisy.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
)

include(GNUInstallDirs)
install(TARGETS x1a_TraceClassic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
