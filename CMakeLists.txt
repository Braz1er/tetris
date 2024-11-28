cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(TTT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.8.0\\mingw_64")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(TTT main.cpp
        tetris.h
        tetris.cpp
        board.cpp
        board.h
        shape.cpp
        shape.h)

target_link_libraries(TTT Qt6::Widgets)