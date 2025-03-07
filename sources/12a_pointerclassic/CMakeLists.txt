cmake_minimum_required(VERSION 3.14)

project(12a_PointerClassic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(12a_PointerClassic
  main.cpp
  pointerclassic.h pointerclassic.cpp
  ../common/elementdata.h ../common/elementdata.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  ../common/stacktraceutils.h
  ../common/stacktraceutils.cpp
)

include(GNUInstallDirs)
install(TARGETS 12a_PointerClassic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
