# logger
The lite C++ logger  
8 microseconds to build and receive a log-message
Write to std::cout and/or std::cerr and/or file
Configurable: safe, safe queue, unsafe

## Usage
```
#include "logger.h"

#define fmt_dtp(message) LOGGER_DATE_TIME_MESSAGE_PLACE_STRING(message)
#define fmt_tp(message)  LOGGER_TIME_MESSAGE_PLACE_STRING(message)

#define logger_instance l

int main()
{
    logger::logger l(logger::logger::level::debug);

    l.log(logger::logger::level::none     , "message_0: custom message will never be output");
    l.log(logger::logger::level::fatal    , "message_1: custom message will be output in fatal mode and higher");
    l.log(logger::logger::level::critical , fmt_dtp ("message_2: default critical message with date and time stamp and path"));
    l.log(logger::logger::level::error    , fmt_tp  ("message_3: default error message with time stamp and path"));
    log_warning_t ("message_4: friendly default warning message with time stamp");
    log_info_dtp  ("message_5: friendly default info message with date and time stamp and path");
    log_verbose   ("message_6: friendly default verbose message with date and time stamp and path");
    log_debug_dt  ("message_7: friendly default debug message with date and time stamp");
    log_trace     ("message_8: friendly default trace message will not be output according to the set logging level");

    log_verbose_t ("speed test");
    log_verbose_t ("speed test");
    log_verbose_t ("speed test");
    log_verbose_t ("speed test");
    log_verbose_t ("speed test");

    return 0;
}
```

## Output
```
fatal    | message_1: custom message will be output in fatal mode and higher
critical | 2022.02.05 18:13:34.172416 | message_2: default critical message with date and time stamp and path | at: main: ../src/main.cpp: 22
error    | 1644059614.172571235 | message_3: default error message with time stamp and path | at: main: ../src/main.cpp: 23
warning  | 1644059614.172581292 | message_4: friendly default warning message with time stamp
info     | 2022.02.05 18:13:34.172590 | message_5: friendly default info message with date and time stamp and path | at: main: ../src/main.cpp: 25
verbose  | 2022.02.05 18:13:34.172605 | message_6: friendly default verbose message with date and time stamp and path | at: main: ../src/main.cpp: 26
debug    | 2022.02.05 18:13:34.172618 | message_7: friendly default debug message with date and time stamp
verbose  | 1644059614.172643032 | speed test
verbose  | 1644059614.172650854 | speed test
verbose  | 1644059614.172658397 | speed test
verbose  | 1644059614.172665940 | speed test
verbose  | 1644059614.172673483 | speed test

```

## Build
make  
make clean  
make install  
make uninstall  
make logger_example.out

QT build

## Author
Ilya Shishkin  
mailto:cortl@8iter.ru

## Links

https://github.com/cortl0/logger

## License
This project is licensed under the GPL v3.0 - see the LICENSE file for details
