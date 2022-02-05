/*
 *   logger
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"

#include <ctime>

namespace logger
{

logger::~logger()
{
#ifdef LOGGER_SAFE_QUEUE
    stop = true;

    while(stop);
#endif

#ifdef LOGGER_LOGGING_TO_FILE
    log_file.close();
#endif
}

logger::logger(enum level minimum_log_level
               #ifdef LOGGER_LOGGING_TO_FILE
               , std::string file_log_path
               #endif
               ) : level_(minimum_log_level)
{
#ifdef LOGGER_LOGGING_TO_FILE
    log_file = std::ofstream(file_log_path, std::ios::out | std::ios_base::binary | std::ios_base::app);

    if (!log_file.is_open())
        throw std::runtime_error("logger::logger(...) - could not open the log file");
#endif

#ifdef LOGGER_SAFE_QUEUE
    thrd = std::thread(action, this);

    thrd.detach();
#endif
}

std::string logger::get_date_time() noexcept(true)
{
    boost::format fmter("%s.%06d");

#define LOGGER_TIME_BUFFER_LENGTH 20
    char time_buffer[LOGGER_TIME_BUFFER_LENGTH];

    auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();

    std::time_t time = std::chrono::duration_cast<std::chrono::seconds>(tp).count();

#ifdef LOGGER_USE_GMT
    std::strftime(time_buffer, LOGGER_TIME_BUFFER_LENGTH, "%Y.%m.%d %H:%M:%S", std::gmtime(&time));
#else
    std::strftime(time_buffer, LOGGER_TIME_BUFFER_LENGTH, "%Y.%m.%d %H:%M:%S", std::localtime(&time));
#endif

    fmter % time_buffer;

    std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(tp);

    fmter % (microseconds % 1000000).count();

    return fmter.str();
}

std::string logger::get_time() noexcept(true)
{
    boost::format fmter("%d.%09d");

    auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();

    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);

    fmter % seconds.count();

    std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(tp);

    fmter % (nanoseconds % 1000000000).count();

    return fmter.str();
}

void logger::log(level level, std::string message) noexcept(true)
{
    if (level_ < level || level::none == level)
        return;

#if defined LOGGER_SAFE_QUEUE || defined LOGGER_SAFE
    mtx.lock();
#endif

#if defined LOGGER_SAFE || defined LOGGER_UNSAFE
    write(level, message);
#elif defined LOGGER_SAFE_QUEUE
    queue_.push(item_message(level, message));
#endif

#if defined LOGGER_SAFE_QUEUE || defined LOGGER_SAFE
    mtx.unlock();
#endif
}

void logger::set_level(level level)
{
    level_ = level;
}

#ifdef LOGGER_SAFE_QUEUE
void logger::action(logger* l) noexcept(true)
{
    std::queue<item_message> local_queue;

    while(!l->stop || l->queue_.size())
    {
        {
            std::unique_lock<std::mutex> lock(l->mtx, std::try_to_lock);

            if(lock.owns_lock())
                if(l->queue_.size())
                    std::swap(l->queue_, local_queue);
        }

        while(local_queue.size())
        {
            l->write(local_queue.front().level, local_queue.front().message);
            local_queue.pop();
        }
    }

    l->stop = false;
}
#endif

void logger::write(level level, const std::string& message) noexcept(true)
{
#ifdef LOGGER_LOGGING_TO_COUT
    std::cout << level_names[(size_t)level] << " | " << message << std::endl;
#endif

#ifdef LOGGER_LOGGING_TO_CERR
    std::cerr << level_names[(size_t)level] << " | " << message << std::endl;
#endif

#ifdef LOGGER_LOGGING_TO_FILE
    log_file << level_names[(size_t)level] << " | " << message << std::endl;
#endif

#ifdef LOGGER_LOGGING_TO_SOCKET
    /* not implemented */
#endif
}

} // !namespace logger
