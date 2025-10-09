CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c11
BUILD_DIR = ../build

# === Цели ===
all: 
	make door_struct
	make list_test
	make stack_test

door_struct:
	$(CC) $(CFLAGS) dmanager_module.c -o $(BUILD_DIR)/Quest_1

list_test:
	$(CC) $(CFLAGS) list_test.c list.c -o $(BUILD_DIR)/Quest_2

stack_test:
	$(CC) $(CFLAGS) stack_test.c stack.c -o $(BUILD_DIR)/Quest_3


# Проверка кода на статическом анализе (Cppcheck)
lint:
	@echo "Running static analysis with Cppcheck..."
	cppcheck --enable=all --inconclusive *.c *.h

# Проверка памяти с Valgrind
valgrind: $(BUILD_DIR)/Quest_1 $(BUILD_DIR)/Quest_2 $(BUILD_DIR)/Quest_3
	@echo "Running Valgrind memory check..."
	valgrind --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/Quest_1
	valgrind --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/Quest_2
	valgrind --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/Quest_3


# Форматирование кода
format:
	clang-format -i *.c *.h

# Очистка
clean:
	rm -f $(BUILD_DIR)/* *.o

.PHONY: all list_test lint valgrind clean
