#pragma once
#include <game/GameObject.hpp>
#include <game/PaddleConfig.h>
#include <SFML/Graphics.hpp>
class Paddle : public GameObject
{
private:
    sf::RectangleShape  rect;
    
    bool moving_down = true;
    const int paddle_width = 5;
    const int paddle_height =  100;
    const int paddle_speed = 10;

    std::unique_ptr<PaddleConfig> config_;
public:
    void initialize(ConstGameContext context) override;
    void update(ConstGameContext context) override;
    void render(sf::RenderTarget* target) override;
    void finalize() override;
    Paddle(std::unique_ptr<PaddleConfig> config);
    ~Paddle();
};

