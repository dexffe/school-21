CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = ../build/graph
SRC = graph.c draw.c inp.c tokenize.c validation.c yard.c eval.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

clean:
	rm -f $(TARGET)
