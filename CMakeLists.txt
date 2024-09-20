cmake_minimum_required(VERSION 3.28)

project(
    SoltysGame
    VERSION 0.0.1
    DESCRIPTION "Soltys Game"
    HOMEPAGE_URL "https://github.com/soltys/SoltysGame"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
string(SUBSTRING ${GIT_SHA1} 0 7 GIT_SHORT_SHA1)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
if (MSVC)    
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS Off)
set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")
include(dependecies)

configure_file("${PROJECT_SOURCE_DIR}/.vscode/launch.json.in" "${PROJECT_SOURCE_DIR}/.vscode/launch.json")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")

add_subdirectory("tools")
add_subdirectory("game")
