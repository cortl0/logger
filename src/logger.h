/*
 *   logger
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#ifndef LOGGER
#define LOGGER

#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <mutex>
#include <queue>
#include <thread>

#include "unistd.h"

namespace logger
{

// logger configurator **************************************************

// Choose
#define LOGGER_LOGGING_TO_FILE
#define LOGGER_LOGGING_TO_COUT
//#define LOGGER_LOGGING_TO_SOCKET /* not implemented */
// !Choose

// Pick one
#define LOGGER_SAFE
//#define LOGGER_SAFE_QUEUE
//#define LOGGER_UNSAFE
// !Pick one

// !logger configurator **************************************************

enum log_level
{
    log_level_none = 0,
    log_level_critical = 1,
    log_level_error = 2,
    log_level_warning = 3,
    log_level_information = 4,
    log_level_debug = 5,
    log_level_trace = 6
};

const std::array<std::string, 7> log_level_names
{
    "none",
    "critical",
    "error",
    "warning",
    "information",
    "debug",
    "trace"
};

#if defined LOGGER_SAFE_QUEUE
struct item_message
{
    log_level level;
    std::string time;
    std::string sender;
    std::string message;

    item_message(log_level level, std::string time, std::string sender, std::string message)
        : level(level), time(time), sender(sender), message(message) {}
};
#endif

class logger
{
    log_level minimum_log_level;
    std::string time_buffer;

#ifdef LOGGER_LOGGING_TO_FILE
    std::ofstream log_file;
#endif

#if defined LOGGER_SAFE_QUEUE || defined LOGGER_SAFE
    std::mutex mtx;
#endif

#if defined LOGGER_SAFE_QUEUE
    volatile bool stop = false;
    std::queue<item_message> q;
    std::thread thrd;
    static void thread_work(logger*);
#endif

    static inline void get_time(std::string&) noexcept;
    inline void write(log_level, std::string time, std::string sender, std::string message) noexcept;

public:

    ~logger();
    logger() = delete;
    explicit logger(log_level minimum_log_level = log_level_trace
#ifdef LOGGER_LOGGING_TO_FILE
        , std::string file_log_path = "log_file.txt"
#endif
        );
    void set_minimum_log_level(log_level minimum_log_level);
    void logging(log_level level, std::string sender, std::string message);

};

} // !namespace logger

#endif // !LOGGER
