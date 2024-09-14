cmake_minimum_required(VERSION 3.14)

project(06a_PointerClassic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(06a_PointerClassic
  main.cpp
  pointerclassic.h pointerclassic.cpp
  ../common/pointerscommon.h ../common/pointerscommon.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
)

include(GNUInstallDirs)
install(TARGETS 06a_PointerClassic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
