/*
 *   logger
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"

int main()
{
    logger::logger l(logger::log_level_debug);

    l.logging(logger::log_level_trace,       "main()", "message_0");
    l.logging(logger::log_level_debug,       "main()", "message_1");
    l.logging(logger::log_level_information, "main()", "message_2");
    l.logging(logger::log_level_warning,     "main()", "message_3");
    l.logging(logger::log_level_error,       "main()", "message_4");
    l.logging(logger::log_level_critical,    "main()", "message_5");
    l.logging(logger::log_level_none,        "main()", "message_6");

    return 0;
}
