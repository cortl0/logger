#
# logger
# Ilya Shishkin
# cortl@yandex.ru
# https://github.com/cortl0/logger
# license GPL v3.0
#

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(logger)

add_library(${PROJECT_NAME}
    logger.cpp
    helpers/file.cpp
    helpers/time.cpp
    )
