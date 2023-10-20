/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef CORTL_LOGGER_HELPERS_TIME
#define CORTL_LOGGER_HELPERS_TIME

#include <string>

namespace cortl::logger::helpers
{

class time
{
public:
    static std::string get_time();
};

} // namespace cortl::logger::helpers

#endif // CORTL_LOGGER_HELPERS_TIME
