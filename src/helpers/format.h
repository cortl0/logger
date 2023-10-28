/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef CORTL_LOGGER_HELPERS_FORMAT
#define CORTL_LOGGER_HELPERS_FORMAT

#include "time.h"

#ifdef CORTL_LOGGER_USE_UNIX_TIME
#define CORTL_LOGGER_APPEND_TIME(message) message.append(cortl::logger::helpers::time::get_unix_time()).append(" | ")
#else
#ifdef CORTL_LOGGER_USE_GMT
#define CORTL_LOGGER_APPEND_TIME(message) message.append(cortl::logger::helpers::time::get_gmt_time()).append(" | ")
#else
#define CORTL_LOGGER_APPEND_TIME(message) message.append(cortl::logger::helpers::time::get_local_time()).append(" | ")
#endif
#endif

#define CORTL_LOGGER_APPEND_LEVEL(message, level) message.append(cortl::logger::logger::get_level_name(level)).append(" | ")
#define CORTL_LOGGER_APPEND_MESSAGE(message_first, message_second) message_first.append(message_second)
#define CORTL_LOGGER_APPEND_END_LINE(message) message.append("\n")

#define CORTL_LOGGER_APPEND_PLACE(message) \
    message.append(" | at function: ").append(std::string(__FUNCTION__)) \
    .append(", file: ").append(__FILE__) \
    .append(", line: ").append(std::to_string(__LINE__))

#define CORTL_LOGGER_FORMAT_WITH_PLACE(message, level) CORTL_LOGGER_APPEND_END_LINE(CORTL_LOGGER_APPEND_PLACE(CORTL_LOGGER_APPEND_MESSAGE(CORTL_LOGGER_APPEND_LEVEL(CORTL_LOGGER_APPEND_TIME(std::string()), level), message)))
#define CORTL_LOGGER_FORMAT_ORDINARY(message, level) CORTL_LOGGER_APPEND_END_LINE(CORTL_LOGGER_APPEND_MESSAGE(CORTL_LOGGER_APPEND_LEVEL(CORTL_LOGGER_APPEND_TIME(std::string()), level), message))

#define CORTL_LOGGER_CURRENT_FORMAT(message, level) CORTL_LOGGER_FORMAT_ORDINARY(message, level)

#ifndef CORTL_LOGGER_DISABLED
#define log_none(message)     if(logger_instance.check_level(cortl::logger::logger::level::none))     logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::none))
#define log_fatal(message)    if(logger_instance.check_level(cortl::logger::logger::level::fatal))    logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::fatal))
#define log_critical(message) if(logger_instance.check_level(cortl::logger::logger::level::critical)) logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::critical))
#define log_syserror(message) if(logger_instance.check_level(cortl::logger::logger::level::syserror)) logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::syserror))
#define log_error(message)    if(logger_instance.check_level(cortl::logger::logger::level::error))    logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::error))
#define log_warning(message)  if(logger_instance.check_level(cortl::logger::logger::level::warning))  logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::warning))
#define log_info(message)     if(logger_instance.check_level(cortl::logger::logger::level::info))     logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::info))
#define log_verbose(message)  if(logger_instance.check_level(cortl::logger::logger::level::verbose))  logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::verbose))
#define log_debug(message)    if(logger_instance.check_level(cortl::logger::logger::level::debug))    logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::debug))
#define log_trace(message)    if(logger_instance.check_level(cortl::logger::logger::level::trace))    logger_instance.log(CORTL_LOGGER_CURRENT_FORMAT(message, cortl::logger::logger::level::trace))
#else
#define log_none(message)
#define log_fatal(message)
#define log_critical(message)
#define log_syserror(message)
#define log_error(message)
#define log_warning(message)
#define log_info(message)
#define log_verbose(message)
#define log_debug(message)
#define log_trace(message)
#endif

#endif // CORTL_LOGGER_HELPERS_FORMAT
