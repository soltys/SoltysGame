#pragma once
#include <memory>
#include <utility>
#include <packer/Packer.h>
#include "Logging/Logger.h"
class Locator
{
private:
    static void provide_packer();
    static void provide_logger();
    inline static std::shared_ptr<packer::Packer> packer_ = nullptr;
    inline static std::shared_ptr<Logger> logger_ = nullptr;

public:
    static packer::Packer *get_packer() { return packer_.get(); }
    static void provide(std::shared_ptr<packer::Packer> packer)
    {
        packer_ = std::move(packer);
    }

    static Logger *get_logger() { return logger_.get(); }
    static void provide(std::shared_ptr<Logger> logger)
    {
        logger_ = std::move(logger);
    }

    static void initialize();
};