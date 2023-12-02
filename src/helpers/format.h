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

#define CORTL_LOGGER_FORMAT_PLACE_STRING \
    std::string(__PRETTY_FUNCTION__).append(":").append(__FILE__).append(":").append(std::to_string(__LINE__))

#define CORTL_LOGGER_FORMAT_ERRNO_STRING \
    std::string("errno [").append(std::to_string(errno)).append("], strerror [").append(strerror(errno)).append("]")

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

    #define CORTL_LOGGER_FORMAT_GOOD_RESULT_LENGTH \
        if(result_length >= 0 && SIZE_MAX != result_length) \
            offset += result_length;

    #ifdef CORTL_LOGGER_USE_HUMAN_READABLE_TIME
        #ifdef CORTL_LOGGER_USE_LOCAL_TIME
            #define CORTL_LOGGER_HUMAN_READABLE_TIME_TYPE std::localtime(&seconds)
        #else
            #define CORTL_LOGGER_HUMAN_READABLE_TIME_TYPE std::gmtime(&seconds)
        #endif

        #define CORTL_LOGGER_FORMAT_APPEND_TIME \
            result_length = std::strftime(buffer + offset, \
                CORTL_LOGGER_FORMAT_BUFFER_LENGTH - offset, "\n%Y.%m.%d %H:%M:%S", \
                CORTL_LOGGER_HUMAN_READABLE_TIME_TYPE); \
            CORTL_LOGGER_FORMAT_GOOD_RESULT_LENGTH

        #define CORTL_LOGGER_FORMAT_OUTPUT_WITH_TIME ".%.9u | %s | %s",
    #else
        #define CORTL_LOGGER_FORMAT_APPEND_TIME

        #define CORTL_LOGGER_FORMAT_OUTPUT_WITH_TIME "\n%.10u.%.9u | %s | %s", seconds,
    #endif

    #define CORTL_LOGGER_FORMAT_ORDINARY(level, message) \
        if(cortl_logger_instance.check_level(level)) \
        { \
            char buffer[CORTL_LOGGER_FORMAT_BUFFER_LENGTH]; \
            size_t offset{}, result_length; \
            auto time = std::chrono::high_resolution_clock::now().time_since_epoch(); \
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count(); \
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() % 1000000000; \
            CORTL_LOGGER_FORMAT_APPEND_TIME \
            result_length = snprintf(buffer + offset, \
                CORTL_LOGGER_FORMAT_BUFFER_LENGTH - offset, \
                CORTL_LOGGER_FORMAT_OUTPUT_WITH_TIME \
                nanoseconds, cortl::logger::logger::get_level_name(level).data(), message); \
            CORTL_LOGGER_FORMAT_GOOD_RESULT_LENGTH \
            cortl_logger_instance.log(buffer, offset); \
        }

    #define log_fatal(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::fatal, message)
    #define log_critical(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::critical, message)
    #define log_syserror(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::syserror, message)
    #define log_error(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::error, message)
    #define log_warning(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::warning, message)
    #define log_info(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::info, message)
    #define log_verbose(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::verbose, message)
    #define log_debug(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::debug, message)
    #define log_trace(message) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::trace, message)

#endif

#endif // CORTL_LOGGER_HELPERS_FORMAT
