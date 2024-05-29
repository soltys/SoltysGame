set(MAIN_TARGET soltys_game_main)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

pack_resources(pack_file
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/assets/pack.json"
	OUTPUT_FILE "${PROJECT_BINARY_DIR}/$<CONFIG>/bin/pack.db"
    FORCE)

add_executable(${MAIN_TARGET} WIN32
    main.cpp
    LogWindow.cpp
    LogWindow.h
    Resources.hpp
    Utils.cpp
    Utils.h
    Game.cpp
    Game.h
    GameTime.hpp
    GameObject.hpp
    Config.h
    Paddle.cpp
    Paddle.h
    ${pack_file}
)

target_link_libraries(${MAIN_TARGET} PRIVATE sfml-graphics sfml-main packer_library)


