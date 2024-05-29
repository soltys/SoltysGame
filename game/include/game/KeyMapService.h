#pragma once
#include <game/composition/composition.hpp>
#include <SFML/Window/Keyboard.hpp>

typedef std::string action_name;
typedef sf::Keyboard::Key key_name;
typedef std::map<action_name, key_name> KeyMap;
typedef std::map<game::Location, KeyMap> PlayerKeyMap;
class KeyMapService
{
protected:
    PlayerKeyMap maps;

public:
    const PlayerKeyMap &get_player_key_map() const { return maps; }
    const key_name &get_key(game::Location loc, action_name action_name)
    {
        return maps[loc][action_name];
    }
};

class KeyJsonMapService : public KeyMapService
{
public:
    static KeyJsonMapService parse(std::string json);
};