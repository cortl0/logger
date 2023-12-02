# logger
The lite thread safe C++ logger  
1100 nanoseconds to build and write a log message  
Write to file by file_descriptor such as cout, cerr, regular and all other files  
You can use helpers or message format according to your own preferences  
  
## Test
1200 nanoseconds in UNIX time mode
```
1701366792.820565802 | info     | speed test
1701366792.820566839 | info     | speed test
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

inline cortl::logger::helpers::file cortl_file_helper;
inline cortl::logger::logger cortl_logger_instance;

int main(int argc, char **argv)
{
    using namespace cortl::logger;

    cortl_file_helper.set_descriptor(helpers::file::open("/dev/shm/log.txt"));
    cortl_logger_instance.set_descriptor(cortl_file_helper.get_descriptor());
    cortl_logger_instance.set_level(logger::level::debug);
    log_syserror(CORTL_LOGGER_FORMAT_ERRNO_STRING.c_str());
    log_info(CORTL_LOGGER_FORMAT_PLACE_STRING.c_str());
    log_debug("message will be output in debug mode and higher");
    log_trace("message will be output in trace mode but will not be output now according to the defined logging level (debug)");

    for(int i = 0; i < 1000000; ++i)
        log_info("speed test");

    return 0;
}
```

## Output
```
1701366791.660527647 | syserror | errno [0], strerror [Success]
1701366791.660629898 | info     | int main(int, char**):./logger/src/logger_test.cpp:24
1701366791.660657787 | debug    | message will be output in debug mode and higher
...
1701366792.820564773 | info     | speed test
1701366792.820565802 | info     | speed test
1701366792.820566839 | info     | speed test
1701366792.820567891 | info     | speed test
...

$ ctest
Total Test time (real) =   1.17 sec
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
