#pragma once
#include <memory>
#include <utility>
#include <packer/Packer.h>
#include <game/logging/Logger.h>
#include <game/KeyMapService.h>
class Locator
{
private:
    static void provide_packer();
    static void remove_packer_if_exists(const std::filesystem::path packer_path);
    static std::filesystem::path get_packer_path();
    static void extract_packer_from_executable(const std::filesystem::path packer_path);
    static void provide_logger();
    static void provide_key_map();
    inline static std::shared_ptr<packer::Packer> packer_ = nullptr;
    inline static std::shared_ptr<Logger> logger_ = nullptr;
    inline static std::shared_ptr<KeyMapService> key_map_service_ = nullptr;

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

    static KeyMapService *get_key_map() { return key_map_service_.get(); }
    static void provide(std::shared_ptr<KeyMapService> key_map_service)
    {
        key_map_service_ = std::move(key_map_service);
    }

    static void initialize();
};