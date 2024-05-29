set(MAIN_TARGET soltys_game_main)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

set(SOURCES 
    main.cpp
)

add_executable(${MAIN_TARGET} WIN32 
    ${SOURCES}
)





# add c++ 11
target_compile_features(${MAIN_TARGET} PUBLIC cxx_std_14)
set_target_properties(${MAIN_TARGET} PROPERTIES CXX_EXTENSIONS OFF)

# Change output name
set_target_properties(${MAIN_TARGET} PROPERTIES OUTPUT_NAME ${MAIN_TARGET_DISPLAY_NAME})
set_target_properties(${MAIN_TARGET} PROPERTIES PROJECT_LABEL ${MAIN_TARGET_DISPLAY_NAME})

if(MSVC) 
    # set main project as default one in Visual Studio (Set as Startup Project)
    set_property(DIRECTORY ../ PROPERTY VS_STARTUP_PROJECT ${MAIN_TARGET})
endif()

# Libraries
target_link_libraries(${MAIN_TARGET} 
PRIVATE 
    Allegro::allegro
    Allegro::allegro_primitives
)

