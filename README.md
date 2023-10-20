# logger
The lite C++ logger  
6 microseconds to build and write a log-message  
Write to file by file_descriptor such as cout, cerr and all other files

## Usage
```
#include "logger.h"
#include "helpers/format.h"

#define logger_instance logger_
inline cortl::logger::logger logger_;

int main()
{
    logger_.set_level(cortl::logger::logger::level::debug);
    logger_.log("message_0: message will be output allways\n");
    logger_.log(cortl::logger::logger::level::none , "message_1: message will never be output\n");
    logger_.log(cortl::logger::logger::level::fatal , "message_2: message will be output in fatal mode and higher\n");
    logger_.log(cortl::logger::logger::level::info , "message_3: message will be output in info mode and higher\n");
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
2023.10.20 22:45:10.062209302 | verbose  | message_4: user-friendly message will be output in verbose mode and higher
2023.10.20 22:45:10.062376475 | info     | speed test
2023.10.20 22:45:10.062398010 | info     | speed test
2023.10.20 22:45:10.062418407 | info     | speed test
2023.10.20 22:45:10.062434011 | info     | speed test
2023.10.20 22:45:10.062450826 | info     | speed test
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
