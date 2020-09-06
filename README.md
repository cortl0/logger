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
	
	l.logging(logger::log_level_trace,       "main()", "message_0");
	l.logging(logger::log_level_debug,       "main()", "message_1");
	l.logging(logger::log_level_information, "main()", "message_2");
	l.logging(logger::log_level_warning,     "main()", "message_3");
	l.logging(logger::log_level_error,       "main()", "message_4");
	l.logging(logger::log_level_critical,    "main()", "message_5");
	l.logging(logger::log_level_none,        "main()", "message_6");
	
	return 0;
}
```

## Output
```
2020.09.06 08:28:41.594492 | debug | main() | message_1
2020.09.06 08:28:41.594623 | information | main() | message_2
2020.09.06 08:28:41.594646 | warning | main() | message_3
2020.09.06 08:28:41.594665 | error | main() | message_4
2020.09.06 08:28:41.594683 | critical | main() | message_5
```

## Build
make  
make clean  
QT build

## Author
Ilya Shishkin  
mailto:cortl@8iter.ru

## Links

https://github.com/cortl0/logger

## License
This project is licensed under the GPL v3.0 - see the LICENSE file for details

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=DPXPWAL9BQD8Q)
