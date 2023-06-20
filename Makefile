CC = g++
CFLAGS = -Wall -Wextra -std=c++11

TARGET = interprocess_communication

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
	rm -f Directory1/*
	rm -f Directory2/*
