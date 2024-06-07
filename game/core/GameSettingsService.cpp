#include <game/core/GameSettingsService.hpp>
GameSettingsJsonService GameSettingsJsonService::parse(std::string json)
{
    auto root = nlohmann::json::parse(json);
    GameSettingsJsonService service;
    service.set_paddle_base_speed(root["paddle"]["base_speed"].get<float>());
    service.set_paddle_base_size(game::Size(root["paddle"]["base_size"]["width"].get<float>(),
                                  root["paddle"]["base_size"]["height"].get<float>()));

    service.set_ball_base_speed(root["ball"]["base_speed"].get<float>());
    service.set_ball_base_size(game::Size(root["ball"]["base_size"]["width"].get<float>(),
                                root["ball"]["base_size"]["height"].get<float>()));

    return service;
}