/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"

#include "time_helper.h"

namespace logger
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
    return logger::logger::level_names[static_cast<size_t>(level)];
}

void logger::log(level level, const std::string& message) const noexcept
{
    if (!check_level(level))
        return;

    log(message);
}

void logger::log(const std::string& message) const noexcept
{
    static constexpr int error{-1};

    for(int attempt = 0; attempt < 2; ++attempt)
        if(::write(file_descriptor_, message.c_str(), message.size()) != error)
            return;
}

void logger::set_file_descriptor(int file_descriptor) noexcept
{
    this->file_descriptor_ = file_descriptor;
}

void logger::set_level(level level) noexcept
{
    this->level_ = level;
}

} // namespace logger
