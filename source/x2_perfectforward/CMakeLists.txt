cmake_minimum_required(VERSION 3.14)

project(x2_PerfectForward LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(x2_PerfectForward
  main.cpp
)

include(GNUInstallDirs)
install(TARGETS x2_PerfectForward
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
