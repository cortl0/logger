/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "time_helper.h"

#include <string.h>
#include <chrono>

namespace logger
{

std::string time_helper::get_date_time() noexcept(true)
{
#define LOGGER_TIME_BUFFER_LENGTH 30

    char time_buffer[LOGGER_TIME_BUFFER_LENGTH];
    auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
    std::time_t time = std::chrono::duration_cast<std::chrono::seconds>(tp).count();

#ifdef LOGGER_USE_GMT
    std::strftime(time_buffer, LOGGER_TIME_BUFFER_LENGTH, "%Y.%m.%d %H:%M:%S", std::gmtime(&time));
#else
    std::strftime(time_buffer, LOGGER_TIME_BUFFER_LENGTH, "%Y.%m.%d %H:%M:%S", std::localtime(&time));
#endif

    std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(tp);
    std::string mcs = "." + std::to_string(nanoseconds.count() % 1000000000);
    strncpy(&time_buffer[19], mcs.c_str(), mcs.size() + 1);

    return time_buffer;
}

std::string time_helper::get_time() noexcept(true)
{
    std::string s;
    auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
    s += std::to_string(seconds.count());
    s += ".";
    std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(tp);
    s += std::to_string((nanoseconds % 1000000000).count());

    return s;
}

} // namespace logger
