#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80
#define UI_ROW 26

#define ALIVE_CELL '#'
#define DEAD_CELL ' '

void init_ncurses();
void draw_field(int current_field[HEIGHT][WIDTH], int speed);
int count_alive_neighbors(const int current_field[HEIGHT][WIDTH], int x, int y);
void update_field(int current_field[HEIGHT][WIDTH], int next_field[HEIGHT][WIDTH]);
void end_game();
int game_loop(int current_field[HEIGHT][WIDTH], int future_field[HEIGHT][WIDTH]);
int read_initial_state_from_stdin(int current_field[HEIGHT][WIDTH]);
void reload_terminal();

int main() {
    int current_field[HEIGHT][WIDTH], future_field[HEIGHT][WIDTH];
    init_ncurses();
    read_initial_state_from_stdin(current_field);
    reload_terminal();
    game_loop(current_field, future_field);
    end_game();
    return 0;
}

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void draw_field(int current_field[HEIGHT][WIDTH], int speed) {
    clear();
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            char symbol = current_field[x][y] == 1 ? ALIVE_CELL : DEAD_CELL;
            mvaddch(x, y, symbol);
        }
    }

    mvprintw(UI_ROW, 0, "Delay: %d ms | 'a/z' to change speed | 'space' to exit'", speed);
    refresh();
}

int count_alive_neighbors(const int current_field[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            if (dx == 0 && dy == 0) continue;
            if (current_field[(dx + x + HEIGHT) % HEIGHT][(dy + y + WIDTH) % WIDTH] == 1) count++;
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

int read_initial_state_from_stdin(int current_field[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            int val = 0;
            if (scanf("%1d", &val) == 1) {
                current_field[x][y] = (val == 1) ? 1 : 0;
            } else {
                current_field[x][y] = 0;
            }
        }
    }
    return 0;
}

int game_loop(int current_field[HEIGHT][WIDTH], int future_field[HEIGHT][WIDTH]) {
    bool exit_game = false;

    int speed = 400;
    while (!exit_game) {
        draw_field(current_field, speed);
        create_next_field(current_field, future_field);
        napms(speed);
        char key = getch();
        if (key != ERR) {
            if (key == ' ') {
                exit_game = true;
            } else if (key == 'a') {
                speed -= 100;
                if (speed < 50) speed = 50;
            } else if (key == 'z') {
                speed += 100;
                if (speed > 3000) speed = 3000;
            }
        }
        for (int x = 0; x < HEIGHT; x++) {
            for (int y = 0; y < WIDTH; y++) {
                current_field[x][y] = future_field[x][y];
            }
        }
    }
    return 0;
}
void reload_terminal() {
    fclose(stdin);
    stdin = fopen("/dev/tty", "r");
}
