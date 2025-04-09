#pragma once
#include <SFML/Graphics.hpp>
#include <game/composition/composition.hpp>
#include <nlohmann/json.hpp>
#include <string>

class GameSettingsService
{
  private:
    float m_paddle_base_speed;

  public:
    float get_paddle_base_speed()
    {
        return m_paddle_base_speed;
    }

  protected:
    void set_paddle_base_speed(float p_paddle_base_speed)
    {
        m_paddle_base_speed = p_paddle_base_speed;
    }

  private:
    game::Size m_paddle_base_size;

  public:
    game::Size get_paddle_base_size()
    {
        return m_paddle_base_size;
    }

  protected:
    void set_paddle_base_size(game::Size p_paddle_base_speed)
    {
        m_paddle_base_size = p_paddle_base_speed;
    }

  private:
    float m_ball_base_speed;

  public:
    float get_ball_base_speed()
    {
        return m_ball_base_speed;
    }

  protected:
    void set_ball_base_speed(float p_paddle_base_speed)
    {
        m_ball_base_speed = p_paddle_base_speed;
    }

  private:
    game::Size m_ball_base_size;

  public:
    game::Size get_ball_base_size()
    {
        return m_ball_base_size;
    }

  protected:
    void set_ball_base_size(game::Size p_paddle_base_speed)
    {
        m_ball_base_size = p_paddle_base_speed;
    }
};

class GameSettingsJsonService : public GameSettingsService
{
  public:
    static GameSettingsJsonService parse(std::string json);
};
