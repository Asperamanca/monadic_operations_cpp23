cmake_minimum_required(VERSION 3.14)

project(13b_WriterMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(13b_WriterMonad
  main.cpp
  writermonad.h
  testwriter.h testwriter.cpp
  ../common/sharedfunctions.h
  ../common/sharedfunctions.cpp
  ../common/printutils.h
  writermonad.cpp
)

target_include_directories(13b_WriterMonad PRIVATE ../extern/)


include(GNUInstallDirs)
install(TARGETS 13b_WriterMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
