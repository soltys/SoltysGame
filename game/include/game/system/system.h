#pragma once
#include <game/GameContext.hpp>
namespace sys
{
    void clear_velocity(const GameContext *context);
    void keyboard(const GameContext *context);
    void collision(const GameContext *context);
    void movement(const GameContext *context);
    void render(const GameContext *context);
}