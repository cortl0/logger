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

    l.logging(logger::log_level_trace,       sndr,     "message_0");
    l.logging(logger::log_level_debug,       sndr,     "message_1");
    l.logging(logger::log_level_information, sndr,     "message_2");
    l.logging(logger::log_level_warning,     "sender", "message_3");
    l.logging(logger::log_level_error,       sndr,     "message_4");
    l.logging(logger::log_level_critical,    sndr,     "message_5");
    l.logging(logger::log_level_none,        sndr,     "message_6");

    return 0;
}
