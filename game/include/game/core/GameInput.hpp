#pragma once
#include <set>
class GameInput
{
    std::set<int> pressed_keys_codes;

public:
    void on_key_pressed(int code)
    {
        pressed_keys_codes.insert(code);
    }
    void on_key_released(int code)
    {
        pressed_keys_codes.erase(code);
    }
    bool is_key_pressed(int code)
    {
        return pressed_keys_codes.count(code) == 1;
    }
};