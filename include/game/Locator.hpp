#pragma once
#include <memory>
#include <utility>
#include <packer/Packer.hpp>
#include <game/logging/Logger.hpp>
#include <game/core/KeyMapService.hpp>
#include <game/core/GameSettingsService.hpp>
#include <game/core/GameInput.hpp>
#include <game/core/FontService.hpp>
#include <game/core/ToggleService.hpp>
#define LOCATOR_FIELD(type, name)                             \
private:                                                      \
    static void provide_##name();                             \
    inline static std::shared_ptr<##type> m_##name = nullptr; \
                                                              \
public:                                                       \
    ##type static *                                           \
        get_##name() { return m_##name.get(); }               \
    static void provide(std::shared_ptr<##type>##name)        \
    {                                                         \
        m_##name = std::move(##name);                         \
    }
class Locator
{
private:
    LOCATOR_FIELD(packer::Packer, packer)
    LOCATOR_FIELD(Logger, logger)
    LOCATOR_FIELD(KeyMapService, key_map)
    LOCATOR_FIELD(GameSettingsService, game_settings)
    LOCATOR_FIELD(GameInput, game_input)
    LOCATOR_FIELD(FontService, font_service)
    LOCATOR_FIELD(ToggleService, toggle_service)
public:
    static void initialize();
};