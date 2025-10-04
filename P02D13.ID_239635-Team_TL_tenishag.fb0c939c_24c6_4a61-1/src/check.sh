#!/bin/bash

# check_all_c_files.sh
# Рекурсивно находит ВСЕ .c файлы в текущей директории и подкаталогах,
# проверяет их форматирование, статический анализ (cppcheck),
# компиляцию и запускает через Valgrind.

set -euo pipefail

# Цвета
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log() { echo -e "${BLUE}[INFO]${NC} $1"; }
warn() { echo -e "${YELLOW}[WARN]${NC} $1"; }
error() { echo -e "${RED}[ERROR]${NC} $1" >&2; }
success() { echo -e "${GREEN}[OK]${NC} $1"; }

# Проверка зависимостей
check_dependencies() {
    local missing=()
    for cmd in gcc clang-format valgrind find cppcheck; do
        if ! command -v "$cmd" &> /dev/null; then
            missing+=("$cmd")
        fi
    done
    if [ ${#missing[@]} -ne 0 ]; then
        error "Отсутствуют зависимости: ${missing[*]}"
        error "Установите: sudo apt install build-essential clang-format valgrind cppcheck"
        exit 1
    fi
}

# Проверка форматирования
check_format() {
    local file="$1"
    local temp=$(mktemp)
    cp "$file" "$temp"
    clang-format -i "$file"
    if cmp -s "$file" "$temp"; then
        rm "$temp"
        return 0
    else
        cp "$temp" "$file"
        rm "$temp"
        return 1
    fi
}

# Запуск cppcheck
run_cppcheck() {
    local file="$1"
    cppcheck --enable=all \
             --suppress=missingIncludeSystem \
             --quiet \
             --error-exitcode=1 \
             "$file" >/dev/null 2>&1
}

# Компиляция
compile_file() {
    local src="$1"
    local exe="${src%.*}.out"
    gcc -std=c11 -Wall -Wextra -Werror -g -O0 -o "$exe" "$src" -lncurses
}

# Запуск Valgrind
run_valgrind() {
    local exe="$1"
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --error-exitcode=1 \
             --quiet \
             "$exe" < /dev/null > /dev/null 2>&1
}

# Обработка одного файла
process_file() {
    local file="$1"
    log "Обработка: $file"

    local failed=0
    local exe="${file%.*}.out"

    # 1. Форматирование
    if ! check_format "$file"; then
        warn "Форматирование не соответствует clang-format: $file"
        ((failed++))
    fi

    # 2. Cppcheck
    if ! run_cppcheck "$file"; then
        error "Cppcheck обнаружил ошибки: $file"
        ((failed++))
    fi

    # 3. Компиляция
    if ! compile_file "$file" 2>/dev/null; then
        error "Ошибка компиляции: $file"
        ((failed++))
    else
        # 4. Valgrind
        if [[ -f "$exe" ]]; then
            if ! run_valgrind "$exe"; then
                error "Valgrind обнаружил ошибки: $file"
                ((failed++))
            fi
            rm -f "$exe"
        fi
    fi

    if [[ $failed -eq 0 ]]; then
        success "✅ $file — OK"
        return 0
    else
        error "❌ $file — FAILED"
        return 1
    fi
}

# Основная функция
main() {
    check_dependencies

    log "Поиск всех .c файлов в текущей директории и подкаталогах..."
    mapfile -d '' c_files < <(find . -type f -name "*.c" -print0)

    if [ ${#c_files[@]} -eq 0 ]; then
        error "Не найдено ни одного .c файла"
        exit 1
    fi

    total=${#c_files[@]}
    passed=0
    failed=0

    log "Найдено файлов: $total"

    for file in "${c_files[@]}"; do
        if process_file "$file"; then
            ((passed++))
        else
            ((failed++))
        fi
    done

    echo
    log "=== ИТОГ ==="
    echo "Всего:    $total"
    echo "Успешно:  $passed"
    echo "Ошибки:   $failed"

    if [[ $failed -eq 0 ]]; then
        success "🎉 Все файлы прошли проверку!"
        exit 0
    else
        error "⚠️  $failed файл(ов) не прошли проверку"
        exit 1
    fi
}

main "$@"
