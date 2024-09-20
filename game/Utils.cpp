#include <game/Locator.hpp>
#include <game/Utils.hpp>

bool r::is_on(const std::string &name)
{
    return Locator::get_toggle_service()->is_on(name);
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
// logging section
//
#define LOG_FUNCTION(log_level, name)                                                                                  \
    void l::##name(const std::string &logger, const std::string &message)                                              \
    {                                                                                                                  \
        log(##log_level, logger, message);                                                                             \
    }                                                                                                                  \
    void l::##name(const std::string &message)                                                                         \
    {                                                                                                                  \
        log(##log_level, "GLOBAL_LOGGER", message);                                                                    \
    }

LOG_FUNCTION(LogLevel::INFO, info)
LOG_FUNCTION(LogLevel::WARN, warn)
LOG_FUNCTION(LogLevel::ERROR, error)

void l::log(LogLevel log_level, const std::string &logger, const std::string &message)
{
    Locator::get_logger()->log(log_level, logger, message);
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

///
/// COMP
///
#define LOCTOSTR(enum_value)                                                                                           \
    case game::Direction::##enum_value:                                                                                \
        return #enum_value;
const char *comp::to_string(game::Direction location)
{
    switch (location)
    {
        LOCTOSTR(Down)
        LOCTOSTR(Up)
        LOCTOSTR(Left)
        LOCTOSTR(Right)
    default:
        throw std::invalid_argument("unmapped argument in to_string for Location");
    }
}
#define STRTOLOC(location_value)                                                                                       \
    if (name == #location_value)                                                                                       \
    {                                                                                                                  \
        return game::Direction::##location_value;                                                                      \
    }
game::Direction comp::to_location(std::string name)
{
    STRTOLOC(Left)
    STRTOLOC(Right)
    STRTOLOC(Up)
    STRTOLOC(Down)
    throw std::invalid_argument("string (" + name + ") cannot be mapped into game::Location");
}

#define KEYCONV(key_value)                                                                                             \
    if (key_name == #key_value)                                                                                        \
    {                                                                                                                  \
        return sf::Keyboard::Key::##key_value;                                                                         \
    }
sf::Keyboard::Key mysf::to_key(std::string key_name)
{
    KEYCONV(A)
    KEYCONV(B)
    KEYCONV(C)
    KEYCONV(D)
    KEYCONV(E)
    KEYCONV(F)
    KEYCONV(G)
    KEYCONV(H)
    KEYCONV(I)
    KEYCONV(J)
    KEYCONV(K)
    KEYCONV(L)
    KEYCONV(M)
    KEYCONV(N)
    KEYCONV(O)
    KEYCONV(P)
    KEYCONV(Q)
    KEYCONV(R)
    KEYCONV(S)
    KEYCONV(T)
    KEYCONV(U)
    KEYCONV(V)
    KEYCONV(W)
    KEYCONV(X)
    KEYCONV(Y)
    KEYCONV(Z)
    KEYCONV(Num0)
    KEYCONV(Num1)
    KEYCONV(Num2)
    KEYCONV(Num3)
    KEYCONV(Num4)
    KEYCONV(Num5)
    KEYCONV(Num6)
    KEYCONV(Num7)
    KEYCONV(Num8)
    KEYCONV(Num9)
    KEYCONV(Escape)
    KEYCONV(LControl)
    KEYCONV(LShift)
    KEYCONV(LAlt)
    KEYCONV(LSystem)
    KEYCONV(RControl)
    KEYCONV(RShift)
    KEYCONV(RAlt)
    KEYCONV(RSystem)
    KEYCONV(Menu)
    KEYCONV(LBracket)
    KEYCONV(RBracket)
    KEYCONV(Semicolon)
    KEYCONV(Comma)
    KEYCONV(Period)
    KEYCONV(Apostrophe)
    KEYCONV(Slash)
    KEYCONV(Backslash)
    KEYCONV(Grave)
    KEYCONV(Equal)
    KEYCONV(Hyphen)
    KEYCONV(Space)
    KEYCONV(Enter)
    KEYCONV(Backspace)
    KEYCONV(Tab)
    KEYCONV(PageUp)
    KEYCONV(PageDown)
    KEYCONV(End)
    KEYCONV(Home)
    KEYCONV(Insert)
    KEYCONV(Delete)
    KEYCONV(Add)
    KEYCONV(Subtract)
    KEYCONV(Multiply)
    KEYCONV(Divide)
    KEYCONV(Left)
    KEYCONV(Right)
    KEYCONV(Up)
    KEYCONV(Down)
    KEYCONV(Numpad0)
    KEYCONV(Numpad1)
    KEYCONV(Numpad2)
    KEYCONV(Numpad3)
    KEYCONV(Numpad4)
    KEYCONV(Numpad5)
    KEYCONV(Numpad6)
    KEYCONV(Numpad7)
    KEYCONV(Numpad8)
    KEYCONV(Numpad9)
    KEYCONV(F1)
    KEYCONV(F2)
    KEYCONV(F3)
    KEYCONV(F4)
    KEYCONV(F5)
    KEYCONV(F6)
    KEYCONV(F7)
    KEYCONV(F8)
    KEYCONV(F9)
    KEYCONV(F10)
    KEYCONV(F11)
    KEYCONV(F12)
    KEYCONV(F13)
    KEYCONV(F14)
    KEYCONV(F15)
    KEYCONV(Pause)

    throw std::invalid_argument("string (" + key_name + ") cannot be mapped into sf::Keyboard::Key");
}

sf::View mysf::get_letterbox_view(sf::View view, int windowWidth, int windowHeight)
{

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to achieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = (float)windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));

    return view;
}