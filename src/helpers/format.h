/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef CORTL_LOGGER_HELPERS_FORMAT
#define CORTL_LOGGER_HELPERS_FORMAT

#include <string.h>

#include <chrono>

#ifdef CORTL_LOGGER_DISABLED

#define log_fatal(message)
#define log_critical(message)
#define log_syserror(message)
#define log_error(message)
#define log_warning(message)
#define log_info(message)
#define log_verbose(message)
#define log_debug(message)
#define log_trace(message)

#else

#ifndef CORTL_LOGGER_FORMAT_BUFFER_LENGTH
    #define CORTL_LOGGER_FORMAT_BUFFER_LENGTH 8192
#endif

#ifdef CORTL_LOGGER_USE_HUMAN_READABLE_TIME
    #ifdef CORTL_LOGGER_USE_LOCAL_TIME
        #define CORTL_LOGGER_HUMAN_READABLE_TIME_TYPE std::localtime(&cortl_logger_seconds)
    #else
        #define CORTL_LOGGER_HUMAN_READABLE_TIME_TYPE std::gmtime(&cortl_logger_seconds)
    #endif

    #define CORTL_LOGGER_APPEND_TIME \
        result_length = std::strftime(cortl_logger_format_string + cortl_logger_format_offset, \
            CORTL_LOGGER_FORMAT_BUFFER_LENGTH - cortl_logger_format_offset, "%Y.%m.%d %H:%M:%S\0", \
            CORTL_LOGGER_HUMAN_READABLE_TIME_TYPE); \
        if(result_length >= 0 && SIZE_MAX != result_length) \
            cortl_logger_format_offset += result_length; \
        result_length = std::snprintf(cortl_logger_format_string + cortl_logger_format_offset, \
            CORTL_LOGGER_FORMAT_BUFFER_LENGTH - cortl_logger_format_offset, \
            ".%.9u\0", cortl_logger_nanoseconds); \
        if(result_length >= 0 && SIZE_MAX != result_length) \
            cortl_logger_format_offset += result_length;
#else
    #define CORTL_LOGGER_APPEND_TIME \
        result_length = std::snprintf(cortl_logger_format_string + cortl_logger_format_offset, \
            CORTL_LOGGER_FORMAT_BUFFER_LENGTH - cortl_logger_format_offset, \
            "%.10u.%.9u\0", cortl_logger_seconds, cortl_logger_nanoseconds); \
        if(result_length >= 0 && SIZE_MAX != result_length) \
            cortl_logger_format_offset += result_length;
#endif

#define CORTL_LOGGER_FORMAT_PREPARE_LOG \
    char cortl_logger_format_string[CORTL_LOGGER_FORMAT_BUFFER_LENGTH]; \
    size_t cortl_logger_format_offset{}; \
    size_t result_length; \
    auto cortl_logger_time = std::chrono::high_resolution_clock::now().time_since_epoch(); \
    auto cortl_logger_seconds = std::chrono::duration_cast<std::chrono::seconds>(cortl_logger_time).count(); \
    auto cortl_logger_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(cortl_logger_time).count() % 1000000000; \
    CORTL_LOGGER_APPEND_TIME

#define CORTL_LOGGER_FORMAT_WRITE_LOG \
    if(result_length >= 0 && SIZE_MAX != result_length) \
    { \
        cortl_logger_format_offset += result_length; \
        cortl_logger_instance.log(cortl_logger_format_string, cortl_logger_format_offset); \
    }

#define CORTL_LOGGER_PLACE_STRING \
    std::string(__PRETTY_FUNCTION__).append(":").append(__FILE__).append(":").append(std::to_string(__LINE__))

#define CORTL_LOGGER_ERRNO_STRING \
    std::string("errno [").append(std::to_string(errno)).append("], strerror [").append(strerror(errno)).append("]")

#define CORTL_LOGGER_FORMAT_ORDINARY(level, message) \
    if(cortl_logger_instance.check_level(level)) \
    { \
        CORTL_LOGGER_FORMAT_PREPARE_LOG \
        result_length = snprintf(cortl_logger_format_string + cortl_logger_format_offset, \
            CORTL_LOGGER_FORMAT_BUFFER_LENGTH - cortl_logger_format_offset, \
            " | %s | %s\n\0", \
            cortl::logger::logger::get_level_name(level).data(), message); \
        CORTL_LOGGER_FORMAT_WRITE_LOG \
    }

#define log_fatal(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::fatal, message)
#define log_critical(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::critical, message)

#define log_syserror(message) \
    if(cortl_logger_instance.check_level(cortl::logger::logger::level::syserror)) \
    { \
        CORTL_LOGGER_FORMAT_PREPARE_LOG \
        result_length = snprintf(cortl_logger_format_string + cortl_logger_format_offset, \
            CORTL_LOGGER_FORMAT_BUFFER_LENGTH - cortl_logger_format_offset, \
            " | %s | %s | %s\n\0", \
            cortl::logger::logger::get_level_name(cortl::logger::logger::level::syserror).data(), message, \
            CORTL_LOGGER_ERRNO_STRING.c_str()); \
        CORTL_LOGGER_FORMAT_WRITE_LOG \
    }

#define log_error(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::error, message)
#define log_warning(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::warning, message)
#define log_info(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::info, message)
#define log_verbose(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::verbose, message)
#define log_debug(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::debug, message)
#define log_trace(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::trace, message)

#endif

#endif // CORTL_LOGGER_HELPERS_FORMAT
