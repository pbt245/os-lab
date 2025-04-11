CC = gcc
CFLAGS = -Wall -std=c11 -pthread
TARGET = pc
SRCS = pc.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
