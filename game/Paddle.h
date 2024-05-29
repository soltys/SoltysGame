#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
class Paddle : public GameObject
{
private:
    sf::RectangleShape  rect;
public:
    void initialize(ConstGameContext context) override;
    void update(ConstGameContext context) override;
    void render(sf::RenderTarget* target) override;
    void finalize() override;
    Paddle(/* args */);
    ~Paddle();
};

