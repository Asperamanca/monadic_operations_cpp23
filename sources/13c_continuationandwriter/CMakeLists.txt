cmake_minimum_required(VERSION 3.16)

project(13c_continuationandwriter LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Concurrent)

add_executable(13c_continuationandwriter
  main.cpp
  testcontinuationwriter.h testcontinuationwriter.cpp
  ../common/sleepy.h ../common/sleepy.cpp
  ../common/elapsed.h ../common/elapsed.cpp
  ../13b_writermonad/writermonad.h ../13b_writermonad/writermonad.cpp
  ../common/printutils.h
)
target_link_libraries(13c_continuationandwriter Qt6::Core Qt6::Concurrent)

include(GNUInstallDirs)
install(TARGETS 13c_continuationandwriter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
