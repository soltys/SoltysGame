#include <game/Locator.h>
#include <game/logging/Logger.h>
#include <game/logging/NullLogger.h>
#include <game/logging/DbLogger.h>
#include <game/logging/WindowsDebugLogger.h>
#include <game/logging/ConsoleLogger.h>
#include <game/logging/CompositeLogger.h>

#include <game/Utils.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <game/resources.h>
#include <fstream>

void Locator::initialize()
{
    Locator::provide_packer();
    Locator::provide_logger();
    Locator::provide_key_map();
    Locator::provide_game_settings();
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
    if (r::get_toggle("LOG_ENABLED"))
    {
        auto composite_logger = std::make_shared<CompositeLogger>();

        if (r::get_toggle("LOG_TO_DB"))
        {
            composite_logger->push_back(std::make_shared<DbLogger>());
        }

        if (r::get_toggle("LOG_TO_WINDOWS_DEBUG"))
        {
            composite_logger->push_back(std::make_shared<WindowsDebugLogger>());
        }

        if (r::get_toggle("LOG_TO_CONSOLE"))
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