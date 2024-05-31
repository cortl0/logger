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

add_compile_options(-Wformat)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# add_compile_definitions(CORTL_LOGGER_DISABLED)
# add_compile_definitions(CORTL_LOGGER_USE_HUMAN_READABLE_TIME)
# add_compile_definitions(CORTL_LOGGER_USE_LOCAL_TIME)

add_executable(${PROJECT_NAME}
    ../src/logger_test.cpp
    )

target_link_libraries(${PROJECT_NAME}
    cortl_logger_with_helpers
    )

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
