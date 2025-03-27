CC = gcc

CFLAGS = -pedantic -std=c11

TARGET = ex5

SRCS = ex5.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) ex5
