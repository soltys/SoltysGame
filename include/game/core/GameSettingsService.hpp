#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <game/composition/composition.hpp>

#define GAME_SETTINGS_FIELD(type, name)                       \
private:                                                      \
    ##type m_##name;                                          \
                                                              \
protected:                                                    \
    void set_##name(##type p_##name) { m_##name = p_##name; } \
                                                              \
public:                                                       \
    ##type get_##name() const { return m_##name; }
class GameSettingsService
{
    GAME_SETTINGS_FIELD(float, paddle_base_speed)
    GAME_SETTINGS_FIELD(game::Size, paddle_base_size)
    GAME_SETTINGS_FIELD(float, ball_base_speed)
    GAME_SETTINGS_FIELD(game::Size, ball_base_size)
};

class GameSettingsJsonService : public GameSettingsService
{
public:
    static GameSettingsJsonService parse(std::string json);
};