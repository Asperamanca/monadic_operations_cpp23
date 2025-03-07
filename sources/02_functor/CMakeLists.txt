cmake_minimum_required(VERSION 3.14)

project(02_Functor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(02_Functor
  main.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  ../common/sharedfunctions.h
  ../common/sharedfunctions.cpp
  testfunctor.h testfunctor.cpp
  functor.h
)

include(GNUInstallDirs)
install(TARGETS 02_Functor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
