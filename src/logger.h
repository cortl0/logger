/*
 *   logger
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef LOGGER
#define LOGGER

#include "unistd.h"

#include <array>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

#include <boost/format.hpp>

#define LOGGER_PLACE_STRING \
    std::string(__FUNCTION__).append(": ") \
    .append(__FILE__).append(": ") \
    .append(std::to_string(__LINE__))

#define LOGGER_TIME_MESSAGE_STRING(message) \
    logger::logger::get_time() \
    .append(" | ").append(message)

#define LOGGER_DATE_TIME_MESSAGE_STRING(message) \
    logger::logger::get_date_time() \
    .append(" | ").append(message)

#define LOGGER_TIME_MESSAGE_PLACE_STRING(message) \
    logger::logger::get_time() \
    .append(" | ").append(message) \
    .append(" | at: ").append(LOGGER_PLACE_STRING)

#define LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message) \
    logger::logger::get_date_time() \
    .append(" | ").append(message) \
    .append(" | at: ").append(LOGGER_PLACE_STRING)

#define log_none_t(message)       logger_instance.log(logger::logger::level::none     , LOGGER_TIME_MESSAGE_STRING(message))
#define log_fatal_t(message)      logger_instance.log(logger::logger::level::fatal    , LOGGER_TIME_MESSAGE_STRING(message))
#define log_critical_t(message)   logger_instance.log(logger::logger::level::critical , LOGGER_TIME_MESSAGE_STRING(message))
#define log_error_t(message)      logger_instance.log(logger::logger::level::error    , LOGGER_TIME_MESSAGE_STRING(message))
#define log_warning_t(message)    logger_instance.log(logger::logger::level::warning  , LOGGER_TIME_MESSAGE_STRING(message))
#define log_info_t(message)       logger_instance.log(logger::logger::level::info     , LOGGER_TIME_MESSAGE_STRING(message))
#define log_verbose_t(message)    logger_instance.log(logger::logger::level::verbose  , LOGGER_TIME_MESSAGE_STRING(message))
#define log_debug_t(message)      logger_instance.log(logger::logger::level::debug    , LOGGER_TIME_MESSAGE_STRING(message))
#define log_trace_t(message)      logger_instance.log(logger::logger::level::trace    , LOGGER_TIME_MESSAGE_STRING(message))

#define log_none_tp(message)      logger_instance.log(logger::logger::level::none     , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_fatal_tp(message)     logger_instance.log(logger::logger::level::fatal    , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_critical_tp(message)  logger_instance.log(logger::logger::level::critical , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_error_tp(message)     logger_instance.log(logger::logger::level::error    , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_warning_tp(message)   logger_instance.log(logger::logger::level::warning  , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_info_tp(message)      logger_instance.log(logger::logger::level::info     , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_verbose_tp(message)   logger_instance.log(logger::logger::level::verbose  , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_debug_tp(message)     logger_instance.log(logger::logger::level::debug    , LOGGER_TIME_MESSAGE_PLACE_STRING(message))
#define log_trace_tp(message)     logger_instance.log(logger::logger::level::trace    , LOGGER_TIME_MESSAGE_PLACE_STRING(message))

#define log_none_dt(message)      logger_instance.log(logger::logger::level::none     , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_fatal_dt(message)     logger_instance.log(logger::logger::level::fatal    , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_critical_dt(message)  logger_instance.log(logger::logger::level::critical , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_error_dt(message)     logger_instance.log(logger::logger::level::error    , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_warning_dt(message)   logger_instance.log(logger::logger::level::warning  , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_info_dt(message)      logger_instance.log(logger::logger::level::info     , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_verbose_dt(message)   logger_instance.log(logger::logger::level::verbose  , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_debug_dt(message)     logger_instance.log(logger::logger::level::debug    , LOGGER_DATE_TIME_MESSAGE_STRING(message))
#define log_trace_dt(message)     logger_instance.log(logger::logger::level::trace    , LOGGER_DATE_TIME_MESSAGE_STRING(message))

#define log_none_dtp(message)     logger_instance.log(logger::logger::level::none     , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_fatal_dtp(message)    logger_instance.log(logger::logger::level::fatal    , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_critical_dtp(message) logger_instance.log(logger::logger::level::critical , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_error_dtp(message)    logger_instance.log(logger::logger::level::error    , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_warning_dtp(message)  logger_instance.log(logger::logger::level::warning  , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_info_dtp(message)     logger_instance.log(logger::logger::level::info     , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_verbose_dtp(message)  logger_instance.log(logger::logger::level::verbose  , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_debug_dtp(message)    logger_instance.log(logger::logger::level::debug    , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))
#define log_trace_dtp(message)    logger_instance.log(logger::logger::level::trace    , LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message))

#define log_none(message)         log_none_dtp     (message)
#define log_fatal(message)        log_fatal_dtp    (message)
#define log_critical(message)     log_critical_dtp (message)
#define log_error(message)        log_error_dtp    (message)
#define log_warning(message)      log_warning_dtp  (message)
#define log_info(message)         log_info_dtp     (message)
#define log_verbose(message)      log_verbose_dtp  (message)
#define log_debug(message)        log_debug_dtp    (message)
#define log_trace(message)        log_trace_dtp    (message)

// logger configurator **************************************************

//#define LOGGER_USE_GMT

// Choose
#define LOGGER_LOGGING_TO_FILE
#define LOGGER_LOGGING_TO_COUT
//#define LOGGER_LOGGING_TO_CERR
//#define LOGGER_LOGGING_TO_SOCKET /* not implemented */
// !Choose

// Pick one
//#define LOGGER_SAFE
#define LOGGER_SAFE_QUEUE
//#define LOGGER_UNSAFE
// !Pick one

// !logger configurator **************************************************

namespace logger
{

class logger
{
public:
    enum class level : size_t
    {
        none,
        fatal,
        critical,
        error,
        warning,
        info,
        verbose,
        debug,
        trace
    };

    const std::array<std::string_view, 9> level_names
    {
        "none    ",
        "fatal   ",
        "critical",
        "error   ",
        "warning ",
        "info    ",
        "verbose ",
        "debug   ",
        "trace   "
    };

#if defined LOGGER_SAFE_QUEUE
    struct item_message
    {
        enum level level;
        std::string message;

        item_message(enum level level, std::string message)
            : level(level), message(message) {}
    };
#endif

    ~logger();
    logger() = delete;

    explicit logger(enum level minimum_log_level = level::trace
        #ifdef LOGGER_LOGGING_TO_FILE
            , std::string file_log_path = "log_file.txt"
        #endif
            );

    void log(level, std::string message) noexcept(true);
    void set_level(level);
    static std::string get_date_time() noexcept(true);
    static std::string get_time() noexcept(true);

private:
    level level_;
    std::string time_buffer;

#ifdef LOGGER_LOGGING_TO_FILE
    std::ofstream log_file;
#endif

#if defined LOGGER_SAFE_QUEUE || defined LOGGER_SAFE
    std::mutex mtx;
#endif

#if defined LOGGER_SAFE_QUEUE
    volatile bool stop = false;
    std::queue<item_message> queue_;
    std::thread thrd;
    static void action(logger*) noexcept(true);
#endif

    inline void write(level, const std::string& message) noexcept(true);
};

} // !namespace logger

#endif // !LOGGER
