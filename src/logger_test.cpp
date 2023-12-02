/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"
#include "helpers/file.h"
#include "helpers/format.h"

inline cortl::logger::helpers::file cortl_file_helper;
inline cortl::logger::logger cortl_logger_instance;

int main(int argc, char **argv)
{
    using namespace cortl::logger;

    cortl_file_helper.set_descriptor(helpers::file::open("/dev/shm/log.txt"));
    cortl_logger_instance.set_descriptor(cortl_file_helper.get_descriptor());
    cortl_logger_instance.set_level(logger::level::debug);
    log_syserror(CORTL_LOGGER_FORMAT_ERRNO_STRING.c_str());
    log_info(CORTL_LOGGER_FORMAT_PLACE_STRING.c_str());
    log_debug("message will be output in debug mode and higher");
    log_trace("message will be output in trace mode but will not be output now according to the defined logging level (debug)");

    for(int i = 0; i < 1000000; ++i)
        log_info("speed test");

    return 0;
}
