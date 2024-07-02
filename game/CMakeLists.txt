set(MAIN_TARGET soltys_game)
set(MAIN_TARGET_DISPLAY_NAME "SoltysGame")

pack_resources(PACK_FILE
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/assets/pack.json"
	OUTPUT_FILE "${PROJECT_BINARY_DIR}/pack.db"
    FORCE)

file(SHA256 ${CMAKE_CURRENT_SOURCE_DIR}/assets/pack.json JSON_SHA256)
string(SUBSTRING ${JSON_SHA256} 0 7 JSON_SHORT_SHA256)

compress_file(PACK_FILE_ZLIB INPUT_FILE "${PACK_FILE}" OUTPUT_FILE "${PROJECT_BINARY_DIR}/pack.db.zlib")

configure_file("game.rc.in" "${PROJECT_BINARY_DIR}/game.rc")
configure_file("config.hpp.in" "${PROJECT_BINARY_DIR}/include/game/config.hpp")
add_subdirectory(assets)

add_executable(${MAIN_TARGET}
    
    main.cpp    
    Utils.cpp
    ${PROJECT_INCLUDE_DIR}/game/Utils.hpp
    Game.cpp
    ${PROJECT_INCLUDE_DIR}/game/Game.hpp
    ${PROJECT_INCLUDE_DIR}/game/GameTime.hpp
    ${PROJECT_INCLUDE_DIR}/game/GameContext.hpp
    ${PROJECT_BINARY_DIR}/include/game/config.hpp

    ${PROJECT_INCLUDE_DIR}/game/core/KeyMapService.hpp
    core/KeyMapService.cpp
    ${PROJECT_INCLUDE_DIR}/game/core/GameSettingsService.hpp
    core/GameSettingsService.cpp
    ${PROJECT_INCLUDE_DIR}/game/core/EnttArchive.hpp
    core/EnttArchive.cpp
    ${PROJECT_INCLUDE_DIR}/game/core/FontService.hpp
    ${PROJECT_INCLUDE_DIR}/game/core/GameInput.hpp
    
    ${PROJECT_INCLUDE_DIR}/miniz/miniz.hpp

    core/PackerProvider.cpp
    ${PROJECT_INCLUDE_DIR}/game/core/PackerProvider.hpp
    
    core/ToggleService.cpp
    ${PROJECT_INCLUDE_DIR}/game/core/ToggleService.hpp
    ${PROJECT_INCLUDE_DIR}/game/core/PackerToggleService.hpp
    ${PROJECT_INCLUDE_DIR}/game/core/MemoryCacheToggleService.hpp
    
    Locator.cpp
    ${PROJECT_INCLUDE_DIR}/game/Locator.hpp

    ${PROJECT_INCLUDE_DIR}/game/logging/Logger.hpp
    ${PROJECT_INCLUDE_DIR}/game/logging/DbLogger.hpp
    logging/DbLogger.cpp
    ${PROJECT_INCLUDE_DIR}/game/logging/CompositeLogger.hpp
    logging/CompositeLogger.cpp
    ${PROJECT_INCLUDE_DIR}/game/logging/NullLogger.hpp
    logging/NullLogger.cpp
    ${PROJECT_INCLUDE_DIR}/game/logging/WindowsDebugLogger.hpp
    logging/WindowsDebugLogger.cpp
    ${PROJECT_INCLUDE_DIR}/game/logging/ConsoleLogger.hpp
    logging/ConsoleLogger.cpp

    ${PACK_FILE_ZLIB}

    system/system.cpp
    system/render.hpp
    system/render.cpp
    system/collision.cpp

    EntityFactory.cpp
    ${PROJECT_INCLUDE_DIR}/game/EntityFactory.hpp
    #single-header-libraries
    ${PROJECT_INCLUDE_DIR}/entt/entt.hpp
    ${PROJECT_INCLUDE_DIR}/nlohmann/json.hpp
    ${PROJECT_VENDOR_DIR}/miniz/miniz.cpp
    ${PROJECT_INCLUDE_DIR}/miniz/miniz.hpp
    "${PROJECT_BINARY_DIR}/game.rc"
)


target_link_libraries(${MAIN_TARGET} PRIVATE sfml-graphics sfml-main packer_library)

target_include_directories(${MAIN_TARGET} PRIVATE ${PROJECT_INCLUDE_DIR} ${PROJECT_BINARY_DIR}/include)