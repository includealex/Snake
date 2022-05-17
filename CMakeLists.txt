cmake_minimum_required(VERSION 3.23.0)
project(GameLib VERSION 1.0.0 DESCRIPTION "Snake game lib")

add_subdirectory(MainAction)

file(GLOB_RECURSE GAME_HEADERS *.h)
file(GLOB_RECURSE GAME_SOURCES *.cpp)

add_library(game STATIC ${GAME_SOURCES} ${GAME_HEADERS})

target_include_directories(game PUBLIC includes/)

set_target_properties (game PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

find_program(CLANG_FORMAT "clang-format" REQUIRED)

add_custom_target (
    format
    COMMAND clang-format
    -i
    -style=file
    ${GAME_HEADERS} ${GAME_SOURCES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")