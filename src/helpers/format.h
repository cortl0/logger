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

    #define log_fatal(args...)
    #define log_critical(args...)
    #define log_syserror(args...)
    #define log_error(args...)
    #define log_warning(args...)
    #define log_info(args...)
    #define log_verbose(args...)
    #define log_debug(args...)
    #define log_trace(args...)

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

        #define CORTL_LOGGER_FORMAT_OUTPUT_WITH_TIME ".%.9ld | %s | ",
    #else
        #define CORTL_LOGGER_FORMAT_APPEND_TIME

        #define CORTL_LOGGER_FORMAT_OUTPUT_WITH_TIME "\n%.10ld.%.9ld | %s | ", seconds,
    #endif

    #define CORTL_LOGGER_FORMAT_ORDINARY(level, args...) \
    { \
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
                nanoseconds, cortl::logger::logger::get_level_name(level).data()); \
            CORTL_LOGGER_FORMAT_GOOD_RESULT_LENGTH \
            result_length = snprintf(buffer + offset, CORTL_LOGGER_FORMAT_BUFFER_LENGTH - offset, args); \
            CORTL_LOGGER_FORMAT_GOOD_RESULT_LENGTH \
            cortl_logger_instance.log(buffer, offset); \
        } \
    }

    #define log_fatal(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::fatal, args)
    #define log_critical(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::critical, args)
    #define log_syserror(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::syserror, args)
    #define log_error(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::error, args)
    #define log_warning(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::warning, args)
    #define log_info(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::info, args)
    #define log_verbose(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::verbose, args)
    #define log_debug(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::debug, args)
    #define log_trace(args...) CORTL_LOGGER_FORMAT_ORDINARY(cortl::logger::logger::level::trace, args)

#endif

#define log_place log_debug(CORTL_LOGGER_FORMAT_PLACE_STRING.c_str())

#endif // CORTL_LOGGER_HELPERS_FORMAT
