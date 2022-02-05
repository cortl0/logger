/*
 *   logger
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"

#define fmt_dtp(message) LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message)
#define fmt_tp(message)  LOGGER_TIME_MESSAGE_PLACE_STRING(message)

#define logger_instance l

int main()
{
    logger::logger l(logger::logger::level::debug);

    l.log(logger::logger::level::none     , "message_0: custom message will never be output");
    l.log(logger::logger::level::fatal    , "message_1: custom message will be output in fatal mode and higher");
    l.log(logger::logger::level::critical , fmt_dtp ("message_2: default critical message with date and time stamp and path"));
    l.log(logger::logger::level::error    , fmt_tp  ("message_3: default error message with time stamp and path"));
    log_warning_t ("message_4: friendly default warning message with time stamp");
    log_info_dtp  ("message_5: friendly default info message with date and time stamp and path");
    log_verbose   ("message_6: friendly default verbose message with date and time stamp and path");
    log_debug_dt  ("message_7: friendly default debug message with date and time stamp");
    log_trace     ("message_8: friendly default trace message will not be output according to the set logging level");

    log_verbose_t ("speed test");
    log_verbose_t ("speed test");
    log_verbose_t ("speed test");
    log_verbose_t ("speed test");
    log_verbose_t ("speed test");

    return 0;
}
