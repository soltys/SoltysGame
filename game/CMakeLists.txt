set(MAIN_TARGET soltys_game_main)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

pack_resources(pack_file
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/pack.json"
	OUTPUT_FILE "${PROJECT_BINARY_DIR}/my_own_pack.sqlite"
    FORCE)

add_executable(${MAIN_TARGET} 
    SFMLMain.cpp
    ${pack_file}
)

add_custom_command(TARGET ${MAIN_TARGET} POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy ${pack_file} $<TARGET_FILE_DIR:${MAIN_TARGET}>
	  COMMAND_EXPAND_LISTS
	  )

target_link_libraries(${MAIN_TARGET} PRIVATE sfml-graphics packer_library)


