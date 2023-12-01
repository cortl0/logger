/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef CORTL_LOGGER_LOGGER
#define CORTL_LOGGER_LOGGER

#include <array>
#include <atomic>
#include <string>

namespace cortl::logger
{

class logger
{
public:
    enum class level : size_t
    {
        none,
        fatal,
        critical,
        syserror,
        error,
        warning,
        info,
        verbose,
        debug,
        trace
    };

    bool check_level(level) const noexcept;
    int get_file_descriptor() const noexcept;
    level get_level() const noexcept;
    static const std::string_view& get_level_name(level) noexcept;
    void log(level, const char* message, size_t count) const noexcept;
    void log(const char* message, size_t count) const noexcept;
    static void log(const std::atomic<int>& file_descriptor_, const char* message, size_t count) noexcept;
    void set_descriptor(int file_descriptor) noexcept;
    void set_level(level) noexcept;

private:
    std::atomic<level> level_{level::info};
    std::atomic<int> file_descriptor_{fileno(stdout)};
};

} // namespace cortl::logger

#endif // CORTL_LOGGER_LOGGER
