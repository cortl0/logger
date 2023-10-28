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
include(CTest)
enable_testing()

project(logger_test)

# add_compile_definitions(CORTL_LOGGER_DISABLED)
# add_compile_definitions(CORTL_LOGGER_USE_GMT)
# add_compile_definitions(CORTL_LOGGER_USE_UNIX_TIME)

add_executable(${PROJECT_NAME}
    ../src/logger_test.cpp
    )

target_link_libraries(${PROJECT_NAME}
    cortl_logger
    cortl_logger_helpers
    )

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
