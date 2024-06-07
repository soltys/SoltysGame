#pragma once
#include <game/composition/composition.hpp>
#include <SFML/Window/Keyboard.hpp>

typedef std::string action_name;
typedef sf::Keyboard::Key key_name;
typedef std::map<action_name, key_name> KeyMap;
typedef std::map<game::Direction, KeyMap> PlayerKeyMap;
class KeyMapService
{
protected:
    PlayerKeyMap maps;

public:
    const key_name &get_key(game::Direction loc, action_name action_name)
    {
        return maps[loc][action_name];
    }
};

class Action
{
public:
    inline static const action_name UP = "Up";
    inline static const action_name DOWN = "Down";
};

class KeyMapJsonService : public KeyMapService
{
public:
    static KeyMapJsonService parse(std::string json);
};