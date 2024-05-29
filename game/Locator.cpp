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

void Locator::initialize()
{
    Locator::provide_packer();
    Locator::provide_logger();
}

void Locator::provide_packer()
{
    wchar_t szPath[MAX_PATH];
    GetModuleFileNameW(NULL, szPath, MAX_PATH);
    const std::filesystem::path exe_path(szPath);
    const auto exe_folder = exe_path.parent_path();
    const auto packer_path = exe_folder / "pack.db";
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