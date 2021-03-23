# logger
The lite C++ logger  
10...50 microseconds to write a line  
Write to std::cout and/or file  
Configurable: safe, safe queue, unsafe

## Usage
```
#include "logger.h"

int main()
{
	logger::logger l(logger::log_level_debug);
	
	l.logging(logger::log_level_trace,       sndr,     "message_0");
	l.logging(logger::log_level_debug,       sndr,     "message_1");
	l.logging(logger::log_level_information, sndr,     "message_2");
	l.logging(logger::log_level_warning,     "sender", "message_3");
	l.logging(logger::log_level_error,       sndr,     "message_4");
	l.logging(logger::log_level_critical,    sndr,     "message_5");
	l.logging(logger::log_level_none,        sndr,     "message_6");
	
	return 0;
}
```

## Output
```
2021.03.23 23:04:29.251019 | debug | file ../src/main.cpp | line 16 | func main | message_1
2021.03.23 23:04:29.251169 | information | file ../src/main.cpp | line 17 | func main | message_2
2021.03.23 23:04:29.251198 | warning | sender | message_3
2021.03.23 23:04:29.251226 | error | file ../src/main.cpp | line 19 | func main | message_4
2021.03.23 23:04:29.251252 | critical | file ../src/main.cpp | line 20 | func main | message_5

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
