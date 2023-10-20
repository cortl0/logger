/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#include "file.h"

#include <unistd.h>

#include <fcntl.h>

namespace cortl::logger::helpers
{

file::~file()
{
    close(descriptor_);
}

int file::get_descriptor() const noexcept
{
    return descriptor_;
}

void file::set_descriptor(int file_descriptor) noexcept
{
    descriptor_ = file_descriptor;
}

int file::close(int file_descriptor) noexcept
{
    return ::close(file_descriptor);
}

int file::open(const std::string& file_name) noexcept
{
    constexpr int permissions{0644};
    return ::open(file_name.c_str(), O_CREAT | O_APPEND | O_WRONLY, permissions);
}

} // namespace cortl::logger::helpers
