cmake_minimum_required(VERSION 3.14)

project(
    SoltysGame
    VERSION 1.0
    DESCRIPTION "Soltys Game"
    HOMEPAGE_URL "https://github.com/soltys/SoltysGame"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(VCPKGCheck)
include(LimitConfiguration)

find_package(Allegro CONFIG REQUIRED)

##
## GAME
## 
add_subdirectory("game")
