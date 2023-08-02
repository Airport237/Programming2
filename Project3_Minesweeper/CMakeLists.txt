cmake_minimum_required(VERSION 3.14)
project(Project3_Minesweeper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Tile.cpp Tile.h Board.cpp Board.h TextureManager.cpp TextureManager.h Random.cpp Random.h)
add_executable(Project3_Minesweeper ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Project3_Minesweeper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)