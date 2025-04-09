#pragma once
#include <game/core/FontService.hpp>
#include <game/core/GameInput.hpp>
#include <game/core/GameSettingsService.hpp>
#include <game/core/KeyMapService.hpp>
#include <game/core/ToggleService.hpp>
#include <game/logging/Logger.hpp>
#include <memory>
#include <packer/Packer.hpp>
#include <utility>
class Locator
{

  public:
    static void initialize();

  private:
    static void provide_packer();
    inline static std::shared_ptr<packer::Packer> m_packer = nullptr;

  public:
    static packer::Packer *get_packer()
    {
        return m_packer.get();
    }
    static void provide(std::shared_ptr<packer::Packer> packer)
    {
        m_packer = std::move(packer);
    }

  private:
    static void provide_logger();
    inline static std::shared_ptr<Logger> m_logger = nullptr;

  public:
    static Logger *get_logger()
    {
        return m_logger.get();
    }
    static void provide(std::shared_ptr<Logger> logger)
    {
        m_logger = std::move(logger);
    }

  private:
    static void provide_key_map();
    inline static std::shared_ptr<KeyMapService> m_key_map = nullptr;

  public:
    static KeyMapService *get_key_map()
    {
        return m_key_map.get();
    }
    static void provide(std::shared_ptr<KeyMapService> key_map)
    {
        m_key_map = std::move(key_map);
    }

  private:
    static void provide_game_settings();
    inline static std::shared_ptr<GameSettingsService> m_game_settings = nullptr;

  public:
    static GameSettingsService *get_game_settings()
    {
        return m_game_settings.get();
    }
    static void provide(std::shared_ptr<GameSettingsService> game_settings)
    {
        m_game_settings = std::move(game_settings);
    }

  private:
    static void provide_game_input();
    inline static std::shared_ptr<GameInput> m_game_input = nullptr;

  public:
    static GameInput *get_game_input()
    {
        return m_game_input.get();
    }
    static void provide(std::shared_ptr<GameInput> game_input)
    {
        m_game_input = std::move(game_input);
    }

  private:
    static void provide_font_service();
    inline static std::shared_ptr<FontService> m_font_service = nullptr;

  public:
    static FontService *get_font_service()
    {
        return m_font_service.get();
    }
    static void provide(std::shared_ptr<FontService> font_service)
    {
        m_font_service = std::move(font_service);
    }

  private:
    static void provide_toggle_service();
    inline static std::shared_ptr<ToggleService> m_toggle_service = nullptr;

  public:
    static ToggleService *get_toggle_service()
    {
        return m_toggle_service.get();
    }
    static void provide(std::shared_ptr<ToggleService> toggle_service)
    {
        m_toggle_service = std::move(toggle_service);
    }
};
