/*
 *   logger
 *   Ilya Shishkin
 *   cortl@yandex.ru
 *   https://github.com/cortl0/logger
 *   licensed by GPL v3.0
 */

#pragma once

#include "../logger.h"
#include "format.h"
#include "file.h"

#define log_place log_debug(CORTL_LOGGER_FORMAT_PLACE_STRING.c_str())

inline cortl::logger::helpers::file cortl_file_helper;
inline cortl::logger::logger cortl_logger_instance;
