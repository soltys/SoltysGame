#pragma once
#include <memory>
#include <vector>
#include <game/GameContext.hpp>
class GameObject
{
public:
    GameObject() = default;
    GameObject(const GameObject &) = default;
    GameObject(const GameObject &&) = delete;
    GameObject &operator=(const GameObject &) = default;
    GameObject &operator=(GameObject &&) = delete;
    virtual ~GameObject() = default;

    virtual void initialize(ConstGameContext context) = 0;
    virtual void update(ConstGameContext context) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
    virtual void finalize() = 0;
};

typedef std::vector<std::unique_ptr<GameObject>> GameObjectCollection;