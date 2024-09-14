cmake_minimum_required(VERSION 3.14)

project(06b_PointerMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(06b_PointerMonad
  main.cpp
  pointermonad.h pointermonad.cpp
  ../common/pointerscommon.h ../common/pointerscommon.cpp
)

include(GNUInstallDirs)
install(TARGETS 06b_PointerMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
