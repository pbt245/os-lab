CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c11

TARGET = ex1

# Source files
SRCS = ex1.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) output.txt
