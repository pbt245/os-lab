CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c11

TARGET = ex2

# Source files
SRCS = ex2.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) output.txt
