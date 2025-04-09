#include "game/composition/composition.hpp"
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
void l::info(const std::string &logger, const std::string &message)
{
    log(LogLevel::INFO, logger, message);
}
void l::info(const std::string &message)
{
    log(LogLevel::INFO, "GLOBAL_LOGGER", message);
}

void l::warn(const std::string &logger, const std::string &message)
{
    log(LogLevel::WARN, logger, message);
}
void l::warn(const std::string &message)
{
    log(LogLevel::WARN, "GLOBAL_LOGGER", message);
}

void l::error(const std::string &logger, const std::string &message)
{
    log(LogLevel::ERROR, logger, message);
}
void l::error(const std::string &message)
{
    log(LogLevel::ERROR, "GLOBAL_LOGGER", message);
}

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
const char *comp::to_string(game::Direction location)
{
    switch (location)
    {
    case game::Direction::Down:
        return "Down";
    case game::Direction::Up:
        return "Up";
    case game::Direction::Left:
        return "Left";
    case game::Direction::Right:
        return "Right";
    default:
        throw std::invalid_argument("unmapped argument in to_string for Location");
    }
}

game::Direction comp::to_location(std::string name)
{
    if (name == "Left")
    {
        return game::Direction::Left;
    }
    if (name == "Right")
    {
        return game::Direction::Right;
    }

    if (name == "Up")
    {
        return game::Direction::Up;
    }
    if (name == "Down")
    {
        return game::Direction::Down;
    }
    throw std::invalid_argument("string (" + name + ") cannot be mapped into game::Location");
}

sf::Keyboard::Key mysf::to_key(std::string key_name)
{
    if (key_name == "A")
    {
        return sf::Keyboard::Key::A;
    }
    if (key_name == "B")
    {
        return sf::Keyboard::Key::B;
    }
    if (key_name == "C")
    {
        return sf::Keyboard::Key::C;
    }
    if (key_name == "D")
    {
        return sf::Keyboard::Key::D;
    }
    if (key_name == "E")
    {
        return sf::Keyboard::Key::E;
    }
    if (key_name == "F")
    {
        return sf::Keyboard::Key::F;
    }
    if (key_name == "G")
    {
        return sf::Keyboard::Key::G;
    }
    if (key_name == "H")
    {
        return sf::Keyboard::Key::H;
    }
    if (key_name == "I")
    {
        return sf::Keyboard::Key::I;
    }
    if (key_name == "J")
    {
        return sf::Keyboard::Key::J;
    }
    if (key_name == "K")
    {
        return sf::Keyboard::Key::K;
    }
    if (key_name == "L")
    {
        return sf::Keyboard::Key::L;
    }
    if (key_name == "M")
    {
        return sf::Keyboard::Key::M;
    }
    if (key_name == "N")
    {
        return sf::Keyboard::Key::N;
    }
    if (key_name == "O")
    {
        return sf::Keyboard::Key::O;
    }
    if (key_name == "P")
    {
        return sf::Keyboard::Key::P;
    }
    if (key_name == "Q")
    {
        return sf::Keyboard::Key::Q;
    }
    if (key_name == "R")
    {
        return sf::Keyboard::Key::R;
    }
    if (key_name == "S")
    {
        return sf::Keyboard::Key::S;
    }
    if (key_name == "T")
    {
        return sf::Keyboard::Key::T;
    }
    if (key_name == "U")
    {
        return sf::Keyboard::Key::U;
    }
    if (key_name == "V")
    {
        return sf::Keyboard::Key::V;
    }
    if (key_name == "W")
    {
        return sf::Keyboard::Key::W;
    }
    if (key_name == "X")
    {
        return sf::Keyboard::Key::X;
    }
    if (key_name == "Y")
    {
        return sf::Keyboard::Key::Y;
    }
    if (key_name == "Z")
    {
        return sf::Keyboard::Key::Z;
    }
    if (key_name == "Num0")
    {
        return sf::Keyboard::Key::Num0;
    }
    if (key_name == "Num1")
    {
        return sf::Keyboard::Key::Num1;
    }
    if (key_name == "Num2")
    {
        return sf::Keyboard::Key::Num2;
    }
    if (key_name == "Num3")
    {
        return sf::Keyboard::Key::Num3;
    }
    if (key_name == "Num4")
    {
        return sf::Keyboard::Key::Num4;
    }
    if (key_name == "Num5")
    {
        return sf::Keyboard::Key::Num5;
    }
    if (key_name == "Num6")
    {
        return sf::Keyboard::Key::Num6;
    }
    if (key_name == "Num7")
    {
        return sf::Keyboard::Key::Num7;
    }
    if (key_name == "Num8")
    {
        return sf::Keyboard::Key::Num8;
    }
    if (key_name == "Num9")
    {
        return sf::Keyboard::Key::Num9;
    }
    if (key_name == "Escape")
    {
        return sf::Keyboard::Key::Escape;
    }
    if (key_name == "LControl")
    {
        return sf::Keyboard::Key::LControl;
    }
    if (key_name == "LShift")
    {
        return sf::Keyboard::Key::LShift;
    }
    if (key_name == "LAlt")
    {
        return sf::Keyboard::Key::LAlt;
    }
    if (key_name == "LSystem")
    {
        return sf::Keyboard::Key::LSystem;
    }
    if (key_name == "RControl")
    {
        return sf::Keyboard::Key::RControl;
    }
    if (key_name == "RShift")
    {
        return sf::Keyboard::Key::RShift;
    }
    if (key_name == "RAlt")
    {
        return sf::Keyboard::Key::RAlt;
    }
    if (key_name == "RSystem")
    {
        return sf::Keyboard::Key::RSystem;
    }
    if (key_name == "Menu")
    {
        return sf::Keyboard::Key::Menu;
    }
    if (key_name == "LBracket")
    {
        return sf::Keyboard::Key::LBracket;
    }
    if (key_name == "RBracket")
    {
        return sf::Keyboard::Key::RBracket;
    }
    if (key_name == "Semicolon")
    {
        return sf::Keyboard::Key::Semicolon;
    }
    if (key_name == "Comma")
    {
        return sf::Keyboard::Key::Comma;
    }
    if (key_name == "Period")
    {
        return sf::Keyboard::Key::Period;
    }
    if (key_name == "Apostrophe")
    {
        return sf::Keyboard::Key::Apostrophe;
    }
    if (key_name == "Slash")
    {
        return sf::Keyboard::Key::Slash;
    }
    if (key_name == "Backslash")
    {
        return sf::Keyboard::Key::Backslash;
    }
    if (key_name == "Grave")
    {
        return sf::Keyboard::Key::Grave;
    }
    if (key_name == "Equal")
    {
        return sf::Keyboard::Key::Equal;
    }
    if (key_name == "Hyphen")
    {
        return sf::Keyboard::Key::Hyphen;
    }
    if (key_name == "Space")
    {
        return sf::Keyboard::Key::Space;
    }
    if (key_name == "Enter")
    {
        return sf::Keyboard::Key::Enter;
    }
    if (key_name == "Backspace")
    {
        return sf::Keyboard::Key::Backspace;
    }
    if (key_name == "Tab")
    {
        return sf::Keyboard::Key::Tab;
    }
    if (key_name == "PageUp")
    {
        return sf::Keyboard::Key::PageUp;
    }
    if (key_name == "PageDown")
    {
        return sf::Keyboard::Key::PageDown;
    }
    if (key_name == "End")
    {
        return sf::Keyboard::Key::End;
    }
    if (key_name == "Home")
    {
        return sf::Keyboard::Key::Home;
    }
    if (key_name == "Insert")
    {
        return sf::Keyboard::Key::Insert;
    }
    if (key_name == "Delete")
    {
        return sf::Keyboard::Key::Delete;
    }
    if (key_name == "Add")
    {
        return sf::Keyboard::Key::Add;
    }
    if (key_name == "Subtract")
    {
        return sf::Keyboard::Key::Subtract;
    }
    if (key_name == "Multiply")
    {
        return sf::Keyboard::Key::Multiply;
    }
    if (key_name == "Divide")
    {
        return sf::Keyboard::Key::Divide;
    }
    if (key_name == "Left")
    {
        return sf::Keyboard::Key::Left;
    }
    if (key_name == "Right")
    {
        return sf::Keyboard::Key::Right;
    }
    if (key_name == "Up")
    {
        return sf::Keyboard::Key::Up;
    }
    if (key_name == "Down")
    {
        return sf::Keyboard::Key::Down;
    }
    if (key_name == "Numpad0")
    {
        return sf::Keyboard::Key::Numpad0;
    }
    if (key_name == "Numpad1")
    {
        return sf::Keyboard::Key::Numpad1;
    }
    if (key_name == "Numpad2")
    {
        return sf::Keyboard::Key::Numpad2;
    }
    if (key_name == "Numpad3")
    {
        return sf::Keyboard::Key::Numpad3;
    }
    if (key_name == "Numpad4")
    {
        return sf::Keyboard::Key::Numpad4;
    }
    if (key_name == "Numpad5")
    {
        return sf::Keyboard::Key::Numpad5;
    }
    if (key_name == "Numpad6")
    {
        return sf::Keyboard::Key::Numpad6;
    }
    if (key_name == "Numpad7")
    {
        return sf::Keyboard::Key::Numpad7;
    }
    if (key_name == "Numpad8")
    {
        return sf::Keyboard::Key::Numpad8;
    }
    if (key_name == "Numpad9")
    {
        return sf::Keyboard::Key::Numpad9;
    }
    if (key_name == "F1")
    {
        return sf::Keyboard::Key::F1;
    }
    if (key_name == "F2")
    {
        return sf::Keyboard::Key::F2;
    }
    if (key_name == "F3")
    {
        return sf::Keyboard::Key::F3;
    }
    if (key_name == "F4")
    {
        return sf::Keyboard::Key::F4;
    }
    if (key_name == "F5")
    {
        return sf::Keyboard::Key::F5;
    }
    if (key_name == "F6")
    {
        return sf::Keyboard::Key::F6;
    }
    if (key_name == "F7")
    {
        return sf::Keyboard::Key::F7;
    }
    if (key_name == "F8")
    {
        return sf::Keyboard::Key::F8;
    }
    if (key_name == "F9")
    {
        return sf::Keyboard::Key::F9;
    }
    if (key_name == "F10")
    {
        return sf::Keyboard::Key::F10;
    }
    if (key_name == "F11")
    {
        return sf::Keyboard::Key::F11;
    }
    if (key_name == "F12")
    {
        return sf::Keyboard::Key::F12;
    }
    if (key_name == "F13")
    {
        return sf::Keyboard::Key::F13;
    }
    if (key_name == "F14")
    {
        return sf::Keyboard::Key::F14;
    }
    if (key_name == "F15")
    {
        return sf::Keyboard::Key::F15;
    }
    if (key_name == "Pause")
    {
        return sf::Keyboard::Key::Pause;
    }

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
