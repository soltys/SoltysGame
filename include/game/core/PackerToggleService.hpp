#pragma once
#include <game/core/ToggleService.hpp>
class PackerToggleService : public ToggleService
{
public:
    bool is_on(const std::string &toggle_name) override;
};
