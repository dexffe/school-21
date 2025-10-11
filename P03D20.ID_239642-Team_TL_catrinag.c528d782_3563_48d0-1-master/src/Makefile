CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -lm
BUILD_DIR = ../build

# === Цели ===
all: 
	make main


main:
	$(CC) $(CFLAGS) main.c evaluator.c parser.c stack.c -o $(BUILD_DIR)/graph


# Проверка кода на статическом анализе (Cppcheck)
lint:
	@echo "Running static analysis with Cppcheck..."
	cppcheck --enable=all --inconclusive *.c *.h

# Проверка памяти с Valgrind
valgrind: $(BUILD_DIR)/graph 
	@echo "Running Valgrind memory check..."
	valgrind --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/graph


# Форматирование кода
format:
	clang-format -i *.c *.h

# Очистка
clean:
	rm -f $(BUILD_DIR)/* *.o *.out

