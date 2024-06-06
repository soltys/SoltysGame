set(MAIN_TARGET soltys_game_main)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

pack_resources(pack_file
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/assets/pack.json"
	OUTPUT_FILE "${PROJECT_BINARY_DIR}/pack.db"
    FORCE)

configure_file("game.rc.in" "${PROJECT_BINARY_DIR}/game.rc")

add_subdirectory(assets)

add_executable(${MAIN_TARGET}
    main.cpp    
    Utils.cpp
    include/game/Utils.h
    Game.cpp
    include/game/Game.h
    include/game/GameTime.hpp
    include/game/GameContext.hpp
    include/game/Config.h

    include/game/core/KeyMapService.h
    core/KeyMapService.cpp
    include/game/core/GameSettingsService.h
    core/GameSettingsService.cpp
    include/game/core/EnttArchive.h
    core/EnttArchive.cpp
    
    Locator.cpp
    include/game/Locator.h

    include/game/logging/Logger.h
    include/game/logging/DbLogger.h
    logging/DbLogger.cpp
    include/game/logging/CompositeLogger.h
    logging/CompositeLogger.cpp
    include/game/logging/NullLogger.h
    logging/NullLogger.cpp
    include/game/logging/WindowsDebugLogger.h
    logging/WindowsDebugLogger.cpp
    include/game/logging/ConsoleLogger.h
    logging/ConsoleLogger.cpp

    ${pack_file}

    system/system.cpp
    system/render.h
    system/render.cpp
    EntityFactory.cpp
    include/game/EntityFactory.h
    #single-header-libraries
    include/entt/entt.hpp
    include/nlohmann/json.hpp

    "${PROJECT_BINARY_DIR}/game.rc"
)


target_link_libraries(${MAIN_TARGET} PRIVATE sfml-graphics sfml-main packer_library)

target_include_directories(${MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)