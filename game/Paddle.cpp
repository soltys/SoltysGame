#include "Paddle.h"

Paddle::Paddle(/* args */)
{
}

void Paddle::initialize(ConstGameContext context)
{
    this->rect = sf::RectangleShape(sf::Vector2f(20, 120));
    rect.setPosition(50, 50);
    rect.setFillColor(sf::Color::White);
}

void Paddle::update(ConstGameContext context)
{
}

void Paddle::render(sf::RenderTarget *target)
{
    target->draw(rect);
}

void Paddle::finalize()
{
}

Paddle::~Paddle()
{
}