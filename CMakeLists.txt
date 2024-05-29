cmake_minimum_required(VERSION 3.14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(VCPKGCheck)
include(LimitConfiguration)

project(
    SoltysGame
    VERSION 1.0
    DESCRIPTION "Soltys Game"
    HOMEPAGE_URL "https://github.com/soltys/SoltysGame"
    LANGUAGES CXX
)

find_package(Allegro5)

##
## MAIN
## 
set(MAIN_TARGET soltys_game_main)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

set(SOURCES 
    src/main.cpp
)

add_executable(${MAIN_TARGET} WIN32 
    ${SOURCES}
)

# set main project as default one in Visual Studio (Set as Startup Project)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${MAIN_TARGET})

# add c++ 11
target_compile_features(${MAIN_TARGET} PUBLIC cxx_std_14)
set_target_properties(${MAIN_TARGET} PROPERTIES CXX_EXTENSIONS OFF)

# Change output name
set_target_properties(${MAIN_TARGET} PROPERTIES OUTPUT_NAME ${MAIN_TARGET_DISPLAY_NAME})
set_target_properties(${MAIN_TARGET} PROPERTIES PROJECT_LABEL ${MAIN_TARGET_DISPLAY_NAME})

# Include directories
target_include_directories(${MAIN_TARGET} 
PUBLIC  
    ${CMAKE_CURRENT_BINARY_DIR}
    ${ALLEGRO_INCLUDE_DIR}
)

# Libraries
target_link_libraries(${MAIN_TARGET} 
PRIVATE 
    ${ALLEGRO_LIBRARY}
    ${ALLEGRO_PRIMITIVES_LIBRARY}
)

# Copy Shared Libraries
add_custom_command(
    TARGET ${MAIN_TARGET} POST_BUILD
    #Allegro 5
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ALLEGRO_SHARED_LIBRARY} "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ALLEGRO_PRIMITIVES_SHARED_LIBRARY} "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>"
)