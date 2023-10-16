# logger
The lite C++ logger  
6 microseconds to build and receive a log-message
Write to file by file_descriptor such as cout, cerr and all other file

## Usage
```
#include "logger.h"
#include "logger_helper.h"

#define logger_instance logger_
logger::logger logger_;

int main()
{
    logger_.set_level(logger::logger::level::debug);
    logger_.log("message_0: message will be output allways\n");
    logger_.log(logger::logger::level::none , "message_1: message will never be output\n");
    logger_.log(logger::logger::level::fatal , "message_2: message will be output in fatal mode and higher\n");
    logger_.log(logger::logger::level::info , "message_3: message will be output in info mode and higher\n");
    log_verbose("message_4: user-friendly message will be output in verbose mode and higher");
    log_trace("message_5: user-friendly message will be output in trace mode but will not be output now according to the defined logging level (debug)");

    log_info("speed test");
    log_info("speed test");
    log_info("speed test");
    log_info("speed test");
    log_info("speed test");

    return 0;
}
```

## Output
```
message_0: message will be output allways
message_2: message will be output in fatal mode and higher
message_3: message will be output in info mode and higher
2023.10.16 22:55:00.333481719 | verbose  | message_4: user-friendly message will be output in verbose mode and higher
2023.10.16 22:55:00.333547436 | info     | speed test
2023.10.16 22:55:00.333553926 | info     | speed test
2023.10.16 22:55:00.333559174 | info     | speed test
2023.10.16 22:55:00.333565396 | info     | speed test
2023.10.16 22:55:00.333574033 | info     | speed test
```

## Build
cmake

## Author
Ilya Shishkin  
mailto:cortl@yandex.ru

## Links
https://github.com/cortl0/logger

## License
This project is licensed under the GPL v3.0 - see the LICENSE file for details
