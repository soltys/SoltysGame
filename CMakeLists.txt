cmake_minimum_required(VERSION 3.14)

project(
    SoltysGame
    VERSION 1.0
    DESCRIPTION "Soltys Game"
    HOMEPAGE_URL "https://github.com/soltys/SoltysGame"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS Off)

include(dependecies)

# include(LimitConfiguration)

# find_package(Allegro CONFIG REQUIRED)

##
## GAME
## 
add_subdirectory("game")
