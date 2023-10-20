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

std::string time::get_time()
{
    constexpr size_t time_buffer_length{30};
    size_t offset{0};

    char time_buffer[time_buffer_length];
    auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
    std::time_t time = std::chrono::duration_cast<std::chrono::seconds>(tp).count();

#ifdef CORTL_LOGGER_USE_UNIX_TIME
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
    offset += snprintf(time_buffer, 11, "%s", std::to_string(seconds.count()).c_str());
#else
#ifdef CORTL_LOGGER_USE_GMT
    offset += std::strftime(time_buffer, time_buffer_length, "%Y.%m.%d %H:%M:%S", std::gmtime(&time));
#else
    offset += std::strftime(time_buffer, time_buffer_length, "%Y.%m.%d %H:%M:%S", std::localtime(&time));
#endif
#endif

    std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(tp);
    snprintf(&time_buffer[offset], 11, ".%.9u\0", nanoseconds.count() % 1000000000);

    return time_buffer;
}

} // namespace cortl::logger::helpers
