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
    include/game/Utils.hpp
    Game.cpp
    include/game/Game.hpp
    include/game/GameTime.hpp
    include/game/GameContext.hpp
    include/game/Config.hpp

    include/game/core/KeyMapService.hpp
    core/KeyMapService.cpp
    include/game/core/GameSettingsService.hpp
    core/GameSettingsService.cpp
    include/game/core/EnttArchive.hpp
    core/EnttArchive.cpp
    
    Locator.cpp
    include/game/Locator.hpp

    include/game/logging/Logger.hpp
    include/game/logging/DbLogger.hpp
    logging/DbLogger.cpp
    include/game/logging/CompositeLogger.hpp
    logging/CompositeLogger.cpp
    include/game/logging/NullLogger.hpp
    logging/NullLogger.cpp
    include/game/logging/WindowsDebugLogger.hpp
    logging/WindowsDebugLogger.cpp
    include/game/logging/ConsoleLogger.hpp
    logging/ConsoleLogger.cpp

    ${pack_file}

    system/system.cpp
    system/render.hpp
    system/render.cpp
    system/collision.cpp

    EntityFactory.cpp
    include/game/EntityFactory.hpp
    #single-header-libraries
    include/entt/entt.hpp
    include/nlohmann/json.hpp

    "${PROJECT_BINARY_DIR}/game.rc"
)


target_link_libraries(${MAIN_TARGET} PRIVATE sfml-graphics sfml-main packer_library)

target_include_directories(${MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)