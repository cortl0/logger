/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "time.h"

#include <string>
#include <chrono>

namespace cortl::logger::helpers
{

#define CORTL_LOGGER_HELPERS_TIME_COMMON_LINES \
    char time_buffer[time_buffer_length]; \
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch(); \
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count(); \
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() % 1000000000;

std::string time::get_gmt_time()
{
    static constexpr size_t time_buffer_length{30};
    size_t offset{0};
    CORTL_LOGGER_HELPERS_TIME_COMMON_LINES
    offset += std::strftime(time_buffer, time_buffer_length, "%Y.%m.%d %H:%M:%S", std::gmtime(&seconds));
    snprintf(&time_buffer[offset], 11, ".%.9u\0", nanoseconds);

    return time_buffer;
}

std::string time::get_local_time()
{
    static constexpr size_t time_buffer_length{30};
    size_t offset{0};
    CORTL_LOGGER_HELPERS_TIME_COMMON_LINES
    offset += std::strftime(time_buffer, time_buffer_length, "%Y.%m.%d %H:%M:%S", std::localtime(&seconds));
    snprintf(&time_buffer[offset], 11, ".%.9u\0", nanoseconds);

    return time_buffer;
}

std::string time::get_unix_time()
{
    static constexpr size_t time_buffer_length{21};
    CORTL_LOGGER_HELPERS_TIME_COMMON_LINES
    snprintf(time_buffer, time_buffer_length, "%.10u.%.9u\0", seconds, nanoseconds);

    return time_buffer;
}

} // namespace cortl::logger::helpers
