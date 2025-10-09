# === Основные настройки ===
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c11

# === Переменные ===
SRC_DIR = .
BUILD_DIR = ../build

MAIN_SRC = $(SRC_DIR)/dmanager_module.c
TEST_SRC = $(SRC_DIR)/list_test.c
COMMON_SRCS = $(wildcard $(SRC_DIR)/list.c $(SRC_DIR)/door_struct.c)
SOURCES = $(MAIN_SRC) $(COMMON_SRCS)
TEST_SOURCES = $(TEST_SRC) $(COMMON_SRCS)

OBJECTS=$(SOURCES:.c=.o)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)

EXECUTABLE = $(BUILD_DIR)/Quest_1
TEST_EXECUTABLE = $(BUILD_DIR)/Quest_2

# === Цели ===
all: $(EXECUTABLE)

list_test: $(TEST_EXECUTABLE)
	@echo "Running tests..."
	./$(TEST_EXECUTABLE)

# Проверка кода на статическом анализе (Cppcheck)
lint:
	@echo "Running static analysis with Cppcheck..."
	cppcheck --enable=all --inconclusive $(SOURCES) $(TEST_SOURCES)

# Проверка памяти с Valgrind
valgrind: $(EXECUTABLE)
	@echo "Running Valgrind memory check..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)

# Создание каталога для сборки
$(BUILD_DIR):
	mkdir -p $@

# Сборка основного исполняемого файла
$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(filter-out %.h,$^) -o $@

# Сборка тестового исполняемого файла
$(TEST_EXECUTABLE): $(TEST_OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(filter-out %.h,$^) -o $@

# Очистка
clean:
	rm -f $(BUILD_DIR)/* $(OBJECTS) $(TEST_OBJECTS)

.PHONY: all list_test lint valgrind clean
