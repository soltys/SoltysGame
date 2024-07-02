#pragma once
#include <string>
class ToggleService
{
public:
    virtual bool is_on(const std::string &toggle_name) = 0;
    virtual ~ToggleService() = 0 {}
};
