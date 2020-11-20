#
#   logger
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/logger
#   licensed by GPL v3.0
#

TARGET=logger

SRCS=logger.cpp

HDRS=logger.h

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

PREFIX_INC=$(PREFIX)/include
PREFIX_LIB=$(PREFIX)/lib

.PHONY: all clean install uninstall $(TARGET)_example.out

all: $(TARGET).so

$(TARGET).so: $(SRCS)
	g++ -std=c++17 -pthread -fPIC -shared -o $(TARGET).so $(SRCS)

clean:
	rm -f $(TARGET).so

install: $(TARGET).so
	install -d $(PREFIX_LIB)
	install -m 644 $(TARGET).so $(PREFIX_LIB)/$(TARGET).so
	install -d $(PREFIX_INC)
	install -t $(PREFIX_INC) $(HDRS)

uninstall:
	cd $(PREFIX_INC); rm $(HDRS);
	cd $(PREFIX_LIB); rm $(TARGET).so;

$(TARGET)_example.out: logger.cpp main.cpp
	g++ -std=c++17 -pthread -o $(TARGET)_example.out logger.cpp main.cpp
