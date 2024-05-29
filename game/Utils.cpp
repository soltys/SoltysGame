#include <game/Utils.h>
#include <game/Locator.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

bool r::get_toggle(const std::string &name)
{
    return Locator::get_packer()->get_toggle(name);
}

std::vector<char> r::get_file(const std::string &name)
{
    return Locator::get_packer()->get_file(name);
}

std::string r::get_string(const std::string &key)
{
    return Locator::get_packer()->get_key_value(key);
}

std::string r::get_locale_string(const std::string &key)
{
    return Locator::get_packer()->get_translation(key, r::get_string("current_locale"));
}

std::vector<packer::LogEntry> r::get_logs(const int amount)
{
    return Locator::get_packer()->get_latest_logs(amount);
}

//
// Logging section
//

void l::info(const std::string &logger, const std::string &message)
{
    Locator::get_logger()->log(LogLevel::INFO, logger, message);
}

void l::info(const std::string &message)
{
    Locator::get_logger()->log(LogLevel::INFO, "GLOBAL_LOGGER", message);
}

///
/// EPOCH
///
std::chrono::local_time<std::chrono::system_clock::duration> epoch::to_local_time_zone(int64_t microseconds_epoch)
{
    auto tp = epoch::to_time_point(microseconds_epoch);
    auto tz = std::chrono::current_zone();
    return tz->to_local(tp);
}
std::string epoch::to_datetime_string(int64_t microseconds_epoch)
{
    return std::format("{:%Y-%m-%d %X}", to_local_time_zone(microseconds_epoch));
}
std::string epoch::to_time_string(int64_t microseconds_epoch)
{
    return std::format("{:%H:%M:%S}", to_local_time_zone(microseconds_epoch));
}
std::chrono::system_clock::time_point epoch::to_time_point(int64_t microseconds_epoch)
{
    using time_point = std::chrono::system_clock::time_point;
    return time_point{std::chrono::duration_cast<time_point::duration>(std::chrono::microseconds(microseconds_epoch))};
}
