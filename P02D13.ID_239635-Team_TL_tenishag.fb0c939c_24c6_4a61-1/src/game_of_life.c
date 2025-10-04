#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80

#define ALIVE_CELL '#'
#define DEAD_CELL ' '

void init_ncurses();
void end_game();
void draw_field(int current_field[HEIGHT][WIDTH]);
int count_alive_neighbors(const int current_field[HEIGHT][WIDTH], int x, int y);
void create_next_field(int current_field[HEIGHT][WIDTH], int future_field[HEIGHT][WIDTH]);
int selecting_the_initial_state(int current_field[HEIGHT][WIDTH]);
int game_loop(int current_field[HEIGHT][WIDTH], int future_field[HEIGHT][WIDTH]);

void init_ncurses() {
    initscr();     // Запустить ncurses-режим
    cbreak();      // Сразу передавать нажатия клавиш (без Enter)
    noecho();      // Не отображать вводимые символы
    curs_set(0);   // Скрыть курсор
    timeout(100);  // getch() будет ждать максимум 100 мс (для плавности)
}

void draw_field(int current_field[HEIGHT][WIDTH]) {
    clear();
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            char symbol = current_field[x][y] == 1 ? ALIVE_CELL : DEAD_CELL;
            mvaddch(x, y, symbol);
        }
    }
    refresh();
}

int count_alive_neighbors(const int current_field[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            if (dx == 0 && dy == 0) continue;
            if (current_field[dx + x][dy + y] == 1) {
                count++;
            }
        }
    }
    return count;
}

void create_next_field(int current_field[HEIGHT][WIDTH], int future_field[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            int count_neighbors = count_alive_neighbors(current_field, x, y);
            if (current_field[x][y] == 1) {
                future_field[x][y] = (count_neighbors == 2 || count_neighbors == 3) ? 1 : 0;
            } else {
                future_field[x][y] = (count_neighbors == 3) ? 1 : 0;
            }
        }
    }
}

void end_game() { endwin(); }

int selecting_the_initial_state(int current_field[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            current_field[x][y] = rand() % 2;
        }
    }
    return 0;
}

int game_loop(int current_field[HEIGHT][WIDTH], int future_field[HEIGHT][WIDTH]) {
    bool exit_game = false;

    double speed = 0.1;
    while (!exit_game) {
        draw_field(current_field);
        create_next_field(current_field, future_field);
        int key = getch();
        if (key == 'space') {
            exit_game = true;
        } else if (key == 'a') {
            speed += 0.1;
        } else if (key == 'z') {
            speed -= 0.1;
        }
        for (int x = 0; x < HEIGHT; x++) {
            for (int y = 0; y < WIDTH; y++) {
                current_field[x][y] = future_field[x][y];
            }
        }
        sleep(speed);
    }
    return 0;
}

int main() {
    int current_field[HEIGHT][WIDTH], future_field[HEIGHT][WIDTH];
    init_ncurses();
    selecting_the_initial_state(current_field);
    game_loop(current_field, future_field);
    end_game();
    return 0;
}
