cmake_minimum_required(VERSION 3.28)

project(
    SoltysGame
    VERSION 0.0.1
    DESCRIPTION "Soltys Game"
    HOMEPAGE_URL "https://github.com/soltys/SoltysGame"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
string(SUBSTRING ${GIT_SHA1} 0 7 GIT_SHORT_SHA1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if (MSVC)    
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS Off)

include(dependecies)

configure_file("${PROJECT_SOURCE_DIR}/.vscode/launch.json.in" "${PROJECT_SOURCE_DIR}/.vscode/launch.json")
##
## GAME
## 
add_subdirectory("game")
