set(MAIN_TARGET soltys_game_main)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

pack_resources(pack_file
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/assets/pack.json"
	OUTPUT_FILE "${PROJECT_BINARY_DIR}/$<CONFIG>/bin/pack.db"
    FORCE)

add_subdirectory(assets)

add_executable(${MAIN_TARGET} WIN32
    main.cpp    
    Utils.cpp
    include/game/Utils.h
    Game.cpp
    include/game/Game.h
    include/game/GameTime.hpp
    include/game/GameObject.hpp
    include/game/GameContext.hpp
    include/game/Config.h
    Paddle.cpp
    include/game/Paddle.h
    include/game/PaddleConfig.h
    Locator.cpp
    include/game/Locator.h
    Logging/LogWindow.cpp
    include/game/Logging/LogWindow.h
    include/game/Logging/Logger.h
    include/game/Logging/DbLogger.h
    Logging/DbLogger.cpp
    include/game/Logging/CompositeLogger.h
    Logging/CompositeLogger.cpp
    include/game/Logging/NullLogger.h
    Logging/NullLogger.cpp
    include/game/Logging/WindowsDebugLogger.h
    Logging/WindowsDebugLogger.cpp
    ${pack_file}
)


target_link_libraries(${MAIN_TARGET} PRIVATE sfml-graphics sfml-main packer_library)

target_include_directories(${MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)