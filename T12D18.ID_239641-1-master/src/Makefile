CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_DIR = ../build

# === Цели ===
all: 
	make main_module_entry_point
	make documentation_module
	make bst_init
	make bst_insert
	make bst_traversal


main_module_entry_point:
	$(CC) $(CFLAGS) main_module_entry_point.c documentation_module.c print_module.c -o $(BUILD_DIR)/Quest_1

documentation_module: 
	$(CC) $(CFLAGS) main_module_entry_point.c documentation_module.c print_module.c -o $(BUILD_DIR)/Quest_2

bst_init:
	$(CC) $(CFLAGS) -D QUEST3 bst.c bst_create_test.c -o $(BUILD_DIR)/Quest_3

bst_insert:
	$(CC) $(CFLAGS) -D QUEST4 bst.c bst_create_test.c -o $(BUILD_DIR)/Quest_4

bst_traversal:
	$(CC) $(CFLAGS) -D QUEST5 bst.c bst_create_test.c -o $(BUILD_DIR)/Quest_5


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
	rm -f $(BUILD_DIR)/* *.o *.out

