cmake_minimum_required(VERSION 3.14)

project(06b_RangeMonad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(06b_RangeMonad
  main.cpp
  rangemonad.h rangemonad.cpp
  ../common/diagnosticinfo.h
  ../common/diagnosticinfo.cpp
  ../common/compilerinfo.h
  ../common/printutils.h
  ../common/noisy.h ../common/noisy.cpp
  ../common/utils.h

)

include(GNUInstallDirs)
install(TARGETS 06b_RangeMonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
