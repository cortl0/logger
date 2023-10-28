# logger
The lite thread safe C++ logger  
1250 nanoseconds to build and write a log message  
Write to file by file_descriptor such as cout, cerr, regular and all other files  
You can use helpers or message format according to your own preferences  
  
## Test
1250 nanoseconds in UNIX time mode
```
1698478158.211970451 | info     | speed test
1698478158.211971597 | info     | speed test
```

1600 nanoseconds in human readable GMT mode
```
2023.10.28 07:32:56.271935180 | info     | speed test
2023.10.28 07:32:56.271936650 | info     | speed test
```

3500 nanoseconds in human readable local time mode
```
2023.10.28 14:24:11.286480313 | info     | speed test
2023.10.28 14:24:11.286483896 | info     | speed test
```

## Test system
Processor: AMD Phenom(tm) II X6 1055T 3300MHz  
Memory: DDR3 Speed: 667 MT/s (dual mode)  

## Usage
```
#include "logger.h"
#include "helpers/file.h"
#include "helpers/format.h"

#define logger_instance logger_
inline cortl::logger::logger logger_;
inline cortl::logger::helpers::file cortl_file_helper;

int main()
{
    using namespace cortl::logger;
    logger_.set_descriptor(helpers::file::open("/dev/shm/log.txt"));
    logger_.set_level(logger::level::debug);
    logger_.log("message_0: message will be output allways\n");
    logger_.log(logger::level::none, "message_1: message will never be output\n");
    logger_.log(logger::level::fatal, "message_2: message will be output in fatal mode and higher\n");
    log_warning("message_3: user-friendly message will be output in warning mode and higher");
    log_verbose("message_4: user-friendly message will be output in verbose mode and higher");
    log_trace("message_5: user-friendly message will be output in trace mode but will not be output now according to the defined logging level (debug)");

    for(int i = 0; i <1000000; ++i)
        log_info("speed test");

    return 0;
}
```

## Output
```
message_0: message will be output allways
message_2: message will be output in fatal mode and higher
2023.10.28 07:37:51.322169352 | warning  | message_3: user-friendly message will be output in warning mode and higher
2023.10.28 07:37:51.322325141 | verbose  | message_4: user-friendly message will be output in verbose mode and higher
...
2023.10.28 07:37:52.895760450 | info     | speed test
2023.10.28 07:37:52.895761896 | info     | speed test
2023.10.28 07:37:52.895763343 | info     | speed test
2023.10.28 07:37:52.895764799 | info     | speed test
2023.10.28 07:37:52.895766247 | info     | speed test
...

$ ctest
Total Test time (real) =   1.57 sec
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
