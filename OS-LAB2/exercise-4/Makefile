CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = ex4
CHILD1 = child1
CHILD2 = child2

all:  $(CHILD1) $(CHILD2) $(TARGET)

$(CHILD1): child1.c
	$(CC) $(CFLAGS) -o $(CHILD1) child1.c

$(CHILD2): child2.c
	$(CC) $(CFLAGS) -o $(CHILD2) child2.c
$(TARGET): ex4.c
	$(CC) $(CFLAGS) -o $(TARGET) ex4.c


clean:
	rm -f $(TARGET) $(CHILD1) $(CHILD2)

run: all
	./$(TARGET)
