#
#   logger
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/logger
#   licensed by GPL v3.0
#

TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += \
    -lpthread \
    -lboost_system

SOURCES += \
    main.cpp \
    logger.cpp

HEADERS += \
    logger.h
