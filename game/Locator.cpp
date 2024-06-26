#include <game/Locator.hpp>
#include <game/logging/Logger.hpp>
#include <game/logging/NullLogger.hpp>
#include <game/logging/DbLogger.hpp>
#include <game/logging/WindowsDebugLogger.hpp>
#include <game/logging/ConsoleLogger.hpp>
#include <game/logging/CompositeLogger.hpp>

#include <game/core/PackerToggleService.hpp>
#include <game/core/MemoryCacheToggleService.hpp>

#include <game/Utils.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <game/resources.hpp>
#include <fstream>

void Locator::initialize()
{
    Locator::provide_packer();
    Locator::provide_toggle_service();

    Locator::provide_logger();
    Locator::provide_key_map();
    Locator::provide_game_settings();
    Locator::provide_game_input();
    Locator::provide_font_service();    
}

std::filesystem::path Locator::get_packer_path()
{
    wchar_t szPath[MAX_PATH];
    GetModuleFileNameW(NULL, szPath, MAX_PATH);
    const std::filesystem::path exe_path(szPath);
    const auto exe_folder = exe_path.parent_path();
    const auto packer_path = exe_folder / "pack.db";
    return packer_path;
}

void Locator::remove_packer_if_exists(const std::filesystem::path packer_path)
{
    if (std::filesystem::exists(packer_path))
    {
        std::filesystem::remove(packer_path);
    }
}

void Locator::extract_packer_from_executable(const std::filesystem::path packer_path)
{
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(IDR_SQLITE1), "sqlite");
    HGLOBAL hMemory = LoadResource(hModule, hResource);
    DWORD dwSize = SizeofResource(hModule, hResource);
    LPVOID lpAddress = LockResource(hMemory);

    char *bytes = new char[dwSize];
    memcpy(bytes, lpAddress, dwSize);
    std::ofstream stream;
    stream.open(packer_path, std::ios::app | std::ios::binary);
    stream.write(bytes, dwSize);
    stream.close();
    delete[] bytes;
}

void Locator::provide_packer()
{
    auto packer_path = get_packer_path();
    remove_packer_if_exists(packer_path);
    extract_packer_from_executable(packer_path);
    Locator::provide(std::make_shared<packer::Packer>(packer_path.generic_string()));
}

void Locator::provide_logger()
{
    if (r::is_on("LOG_ENABLED"))
    {
        auto composite_logger = std::make_shared<CompositeLogger>();

        if (r::is_on("LOG_TO_DB"))
        {
            composite_logger->push_back(std::make_shared<DbLogger>());
        }

        if (r::is_on("LOG_TO_WINDOWS_DEBUG"))
        {
            composite_logger->push_back(std::make_shared<WindowsDebugLogger>());
        }

        if (r::is_on("LOG_TO_CONSOLE"))
        {
            composite_logger->push_back(std::make_shared<ConsoleLogger>());
        }

        provide(composite_logger);
    }
    else
    {
        provide(std::make_shared<NullLogger>());
    }
}

void Locator::provide_key_map()
{
    auto key_map_service = std::make_shared<KeyMapService>(KeyMapJsonService::parse(r::get_string("keymapping")));
    provide(key_map_service);
}

void Locator::provide_game_settings()
{
    auto game_settings_service = std::make_shared<GameSettingsService>(GameSettingsJsonService::parse(r::get_string("game_settings")));
    provide(game_settings_service);
}

void Locator::provide_game_input()
{
    auto game_input = std::make_shared<GameInput>();
    provide(game_input);
}

void Locator::provide_font_service()
{
    auto font_service = std::make_shared<FontService>();
    provide(font_service);
}

void Locator::provide_toggle_service()
{
    auto packer_toggle_service = std::make_shared<PackerToggleService>();
    auto memory_cache_toggle_service = std::make_shared<MemoryCacheToggleService>(packer_toggle_service.get());    
    
    auto all_toggles = Locator::get_packer()->get_toggles();
    preload_collection collection;
    for(const auto& packer_toggle : all_toggles ){
        collection.push_back(std::tuple(packer_toggle.name(), packer_toggle.is_on()));
    }
    memory_cache_toggle_service->preload(collection);

    provide(memory_cache_toggle_service);
}