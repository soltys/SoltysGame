#pragma once
#include <game/GameContext.hpp>
namespace sys
{
    void render_text(const GameContext* context);
    void render_rectangles(const GameContext *context);
    void render_circles(const GameContext *context);
    void render_background(const GameContext *context);
}