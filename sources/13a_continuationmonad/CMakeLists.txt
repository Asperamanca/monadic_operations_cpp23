cmake_minimum_required(VERSION 3.16)

project(13a_continuationmonad LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Concurrent)

add_executable(13a_continuationmonad
  main.cpp
  testcontinuation.h testcontinuation.cpp
  ../common/sleepy.h ../common/sleepy.cpp
  ../common/elapsed.h ../common/elapsed.cpp
  ../common/printutils.h
)
target_link_libraries(13a_continuationmonad Qt6::Core Qt6::Concurrent)

include(GNUInstallDirs)
install(TARGETS 13a_continuationmonad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
