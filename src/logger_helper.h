/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef LOGGER_HELPER
#define LOGGER_HELPER

#include "time_helper.h"

#define LOGGER_APPEND_TIME(message) message.append(logger::time_helper::get_time()).append(" | ")
#define LOGGER_APPEND_DATE_TIME(message) message.append(logger::time_helper::get_date_time()).append(" | ")
#define LOGGER_APPEND_LEVEL(message, level) message.append(logger::logger::get_level_name(level)).append(" | ")
#define LOGGER_APPEND_MESSAGE(message_first, message_second) message_first.append(message_second)
#define LOGGER_APPEND_END_LINE(message) message.append("\n")

#define LOGGER_APPEND_PLACE(message) \
    message.append(" | at function: ").append(std::string(__FUNCTION__)) \
    .append(", file: ").append(__FILE__) \
    .append(", line: ").append(std::to_string(__LINE__))

#define LOGGER_APPEND_FULL(message, level) LOGGER_APPEND_END_LINE(LOGGER_APPEND_PLACE(LOGGER_APPEND_MESSAGE(LOGGER_APPEND_LEVEL(LOGGER_APPEND_DATE_TIME(std::string()), level), message)))
#define LOGGER_APPEND_ORDINARY(message, level) LOGGER_APPEND_END_LINE(LOGGER_APPEND_MESSAGE(LOGGER_APPEND_LEVEL(LOGGER_APPEND_DATE_TIME(std::string()), level), message))
#define LOGGER_APPEND_FAST(message, level) LOGGER_APPEND_END_LINE(LOGGER_APPEND_MESSAGE(LOGGER_APPEND_LEVEL(LOGGER_APPEND_TIME(std::string()), level), message))

#define LOGGER_CURRENT_FORMAT(message, level) LOGGER_APPEND_ORDINARY(message, level)

#define log_none(message)     if(logger_instance.check_level(logger::logger::level::none))     logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::none))
#define log_fatal(message)    if(logger_instance.check_level(logger::logger::level::fatal))    logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::fatal))
#define log_critical(message) if(logger_instance.check_level(logger::logger::level::critical)) logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::critical))
#define log_syserror(message) if(logger_instance.check_level(logger::logger::level::syserror)) logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::syserror))
#define log_error(message)    if(logger_instance.check_level(logger::logger::level::error))    logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::error))
#define log_warning(message)  if(logger_instance.check_level(logger::logger::level::warning))  logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::warning))
#define log_info(message)     if(logger_instance.check_level(logger::logger::level::info))     logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::info))
#define log_verbose(message)  if(logger_instance.check_level(logger::logger::level::verbose))  logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::verbose))
#define log_debug(message)    if(logger_instance.check_level(logger::logger::level::debug))    logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::debug))
#define log_trace(message)    if(logger_instance.check_level(logger::logger::level::trace))    logger_instance.log(LOGGER_CURRENT_FORMAT(message, logger::logger::level::trace))

#endif // LOGGER_HELPER
