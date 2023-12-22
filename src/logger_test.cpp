/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "helpers/log.h"

int main(int argc, char **argv)
{
    cortl_file_helper.set_descriptor(cortl::logger::helpers::file::open("/dev/shm/log.txt"));
    cortl_logger_instance.set_descriptor(cortl_file_helper.get_descriptor());
    cortl_logger_instance.set_level(cortl::logger::logger::level::debug);
    log_place;
    log_syserror(CORTL_LOGGER_FORMAT_ERRNO_STRING.c_str());
    log_debug("message will be output in debug mode and higher");
    log_trace("message will be output in trace mode but will not be output now according to the defined logging level (debug)");
    log_info("test %s [%d]", "snprintf", 12345);

    for(int i = 0; i < 1000000; ++i)
        log_info("speed %s", "test");

    return 0;
}
