/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"

#include <unistd.h>

namespace cortl::logger
{

bool logger::check_level(level l) const noexcept
{
    return l != logger::logger::level::none && l <= level_;
}

int logger::get_file_descriptor() const noexcept
{
    return file_descriptor_;
}

logger::level logger::get_level() const noexcept
{
    return level_;
}

const std::string_view& logger::get_level_name(logger::logger::level level) noexcept
{
    static constexpr std::array<std::string_view, 10> level_names
    {
        "none    ",
        "fatal   ",
        "critical",
        "syserror",
        "error   ",
        "warning ",
        "info    ",
        "verbose ",
        "debug   ",
        "trace   "
    };

    return level_names[static_cast<std::underlying_type_t<logger::level>>(level)];
}

void logger::log(level level, const std::string& message) const noexcept
{
    if (!check_level(level))
        return;

    log(message);
}

void logger::log(const std::string& message) const noexcept
{
    log(file_descriptor_, message);
}

void logger::log(const std::atomic<int>& file_descriptor_, const std::string& message) noexcept
{
    static constexpr int system_call_error{-1};
    static constexpr int ivalid_file_descriptor{-1};

    do
    {
        if(ivalid_file_descriptor == file_descriptor_)
            return;

        if(::write(file_descriptor_, message.c_str(), message.size()) != system_call_error)
            return;
    }
    while(true);
}

void logger::set_descriptor(int file_descriptor) noexcept
{
    file_descriptor_ = file_descriptor;
}

void logger::set_level(level level) noexcept
{
    level_ = level;
}

} // namespace cortl::logger
