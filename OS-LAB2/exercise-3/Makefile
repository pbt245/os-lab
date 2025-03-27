CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c11

TARGET = ex3

SRCS = ex3.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) abc_fifo_name
