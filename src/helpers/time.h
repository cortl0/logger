/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef TIME_HELPER
#define TIME_HELPER

#include "unistd.h"

#include <string>

namespace logger
{

class time_helper
{
public:
    static std::string get_date_time() noexcept(true);
    static std::string get_time() noexcept(true);
};

} // namespace logger

#endif // TIME_HELPER
