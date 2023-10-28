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

#define logger_instance logger_
inline cortl::logger::logger logger_;
inline cortl::logger::helpers::file cortl_file_helper;

int main()
{
    using namespace cortl::logger;
    logger_.set_descriptor(helpers::file::open("/dev/shm/log.txt"));
    logger_.set_level(logger::level::debug);
    logger_.log("message_0: message will be output allways\n");
    logger_.log(logger::level::none, "message_1: message will never be output\n");
    logger_.log(logger::level::fatal, "message_2: message will be output in fatal mode and higher\n");
    log_warning("message_3: user-friendly message will be output in warning mode and higher");
    log_verbose("message_4: user-friendly message will be output in verbose mode and higher");
    log_trace("message_5: user-friendly message will be output in trace mode but will not be output now according to the defined logging level (debug)");

    for(int i = 0; i <1000000; ++i)
        log_info("speed test");

    return 0;
}
