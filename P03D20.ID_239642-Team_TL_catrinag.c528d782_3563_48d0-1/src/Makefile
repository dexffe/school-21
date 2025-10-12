CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = build/graph
SRC = *.c

build:
	mkdir -p build

all: build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm -rf build

rebuild: clean all

run: all
	./$(TARGET)
