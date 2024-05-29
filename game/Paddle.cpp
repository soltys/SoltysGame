#include <game/Paddle.h>
#include <game/Utils.h>
Paddle::Paddle(/* args */)
{
}

void Paddle::initialize(ConstGameContext context)
{
    this->rect = sf::RectangleShape(sf::Vector2f(static_cast<float>(this->paddle_width), static_cast<float>(this->paddle_height)));
    rect.setPosition(20, 20);
    rect.setFillColor(sf::Color::White);
}

void Paddle::update(ConstGameContext context)
{
    auto current_position = rect.getPosition();
    auto window_size = context->get_video_mode();

    if (current_position.y >= ( window_size.height - this->paddle_height))
    {
        this->moving_down = !this->moving_down;
    }
    else if (current_position.y <= 0)
    {
        this->moving_down = !this->moving_down;
    }

    int direction = this->moving_down ? 1 : -1;
    int step = 10 ;
    
    rect.setPosition(current_position.x, current_position.y + (step * direction));
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