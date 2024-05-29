#include <game/Paddle.h>
#include <game/Utils.h>
Paddle::Paddle(std::unique_ptr<PaddleConfig> config): config_(std::move(config))
{
}

void Paddle::initialize(ConstGameContext context)
{
    this->rect = sf::RectangleShape(sf::Vector2f(static_cast<float>(this->paddle_width), static_cast<float>(this->paddle_height)));
    auto start_position = this->config_->get_start_position();
    rect.setPosition(start_position.x, start_position.y);
    rect.setFillColor(sf::Color::White);

    this->moving_down = config_->is_facing_right();
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
    
    
    rect.setPosition(current_position.x, current_position.y + (paddle_speed * direction));
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