cmake_minimum_required(VERSION 3.14)

project(12b_PointerMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(12b_PointerMonad
  main.cpp
  pointermonad.h pointermonad.cpp
  ../common/elementdata.h ../common/elementdata.cpp
  ../common/stacktraceutils.h
  ../common/stacktraceutils.cpp
)

include(GNUInstallDirs)
install(TARGETS 12b_PointerMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
