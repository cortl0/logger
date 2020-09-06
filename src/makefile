#
#   logger
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/logger
#   licensed by GPL v3.0
#

NAME = logger
TARGET = $(NAME).out

make: $(TARGET)

$(TARGET): logger.cpp main.cpp
	g++ -std=c++17 -pthread -o $(TARGET) logger.cpp main.cpp

clean:
	rm $(TARGET)
