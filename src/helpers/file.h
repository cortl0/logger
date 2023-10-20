/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef CORTL_LOGGER_HELPERS_FILE
#define CORTL_LOGGER_HELPERS_FILE

#include <atomic>
#include <string>

namespace cortl::logger::helpers
{

class file
{
public:
    ~file();
    int get_descriptor() const noexcept;
    void set_descriptor(int file_descriptor) noexcept;
    static int close(int file_descriptor) noexcept;
    static int open(const std::string& file_name) noexcept;
private:
    std::atomic<int> descriptor_{-1};
};

} // namespace cortl::logger::helpers

#endif // CORTL_LOGGER_HELPERS_FILE
