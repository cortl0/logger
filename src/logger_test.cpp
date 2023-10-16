/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"
#include "logger_helper.h"

#define logger_instance logger_
logger::logger logger_;

int main()
{
    logger_.set_level(logger::logger::level::debug);
    logger_.log("message_0: message will be output allways\n");
    logger_.log(logger::logger::level::none , "message_1: message will never be output\n");
    logger_.log(logger::logger::level::fatal , "message_2: message will be output in fatal mode and higher\n");
    logger_.log(logger::logger::level::info , "message_3: message will be output in info mode and higher\n");
    log_verbose("message_4: user-friendly message will be output in verbose mode and higher");
    log_trace("message_5: user-friendly message will be output in trace mode but will not be output now according to the defined logging level (debug)");

    log_info("speed test");
    log_info("speed test");
    log_info("speed test");
    log_info("speed test");
    log_info("speed test");

    return 0;
}
