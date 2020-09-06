/*
 *   logger
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "logger.h"

namespace logger
{

logger::~logger()
{
#ifdef LOGGER_SAFE_QUEUE
    while(q.size() != 0)
        usleep(1000);

    stop = true;
#endif

#ifdef LOGGER_LOGGING_TO_FILE
    log_file.close();
#endif
}

logger::logger(log_level minimum_log_level
#ifdef LOGGER_LOGGING_TO_FILE
        , std::string file_log_path
#endif
        ) : minimum_log_level(minimum_log_level)
{
#ifdef LOGGER_LOGGING_TO_FILE
    log_file = std::ofstream(file_log_path, std::ios::out | std::ios_base::binary | std::ios_base::app);

    if (!log_file.is_open())
        throw std::runtime_error("logger::logger(...) - could not open the log file");
#endif

#ifdef LOGGER_SAFE_QUEUE
    thrd = std::thread(thread_work, this);

    thrd.detach();
#endif
}

void logger::set_minimum_log_level(log_level minimum_log_level)
{
    this->minimum_log_level = minimum_log_level;
}

void logger::get_time(std::string& time_str) noexcept
{
#define LOGGER_TIME_BUFFER_LENGTH 20
#define LOGGER_TIME_BUFFER_MS_LENGTH 7
    static char time_buffer[LOGGER_TIME_BUFFER_LENGTH];
    static char time_buffer_ms[LOGGER_TIME_BUFFER_MS_LENGTH];
    static std::time_t time;
    auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
    std::chrono::microseconds mics = std::chrono::duration_cast<std::chrono::microseconds>(tp);
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(tp);
    mics = mics % 1000000;
    time = s.count();
    std::strftime(time_buffer, LOGGER_TIME_BUFFER_LENGTH, "%Y.%m.%d %H:%M:%S", std::localtime(&time));
    std::sprintf( time_buffer_ms, "%.6d", static_cast<int>(mics.count()));
    time_str = time_buffer;
    time_str += ".";
    time_str += time_buffer_ms;
}

void logger::logging(log_level level, std::string sender, std::string message)
{
    if (log_level_none == level)
        return;

    if (minimum_log_level < level)
        return;

#if defined LOGGER_SAFE_QUEUE || defined LOGGER_SAFE
    mtx.lock();
#endif

#if defined LOGGER_SAFE || defined LOGGER_UNSAFE
    get_time(time_buffer);
    write(level, time_buffer, sender, message);
#elif defined LOGGER_SAFE_QUEUE
    get_time(time_buffer);
    q.push(item_message(level, time_buffer, sender, message));
#endif

#if defined LOGGER_SAFE_QUEUE || defined LOGGER_SAFE
    mtx.unlock();
#endif
}

#ifdef LOGGER_SAFE_QUEUE
void logger::thread_work(logger* l)
{
    while(!l->stop)
        if(l->mtx.try_lock())
        {
            if(l->q.size())
            {
                l->write(l->q.front().level, l->q.front().time, l->q.front().sender, l->q.front().message);
                l->q.pop();
            }

            l->mtx.unlock();
        }
}
#endif

void logger::write(log_level level, std::string time, std::string sender, std::string message) noexcept
{
#ifdef LOGGER_LOGGING_TO_COUT
    std::cout << time << " | " << log_level_names[level] << " | " << sender << " | " << message << std::endl;
#endif

#ifdef LOGGER_LOGGING_TO_FILE
    log_file << time << " | " << log_level_names[level] << " | " << sender << " | " << message << std::endl;
#endif
}

}
