#include "draw.h"
#include <math.h>
#include <stdio.h>

void draw_init_buffer(char buf[DRAW_HEIGHT][DRAW_WIDTH]) {
    for (int y = 0; y < DRAW_HEIGHT; y++) {
        for (int x = 0; x < DRAW_WIDTH; x++) {
            buf[y][x] = DRAW_POINT_CHAR;
        }
    }
}

void draw_plot_samples(const double samples[DRAW_WIDTH], char buf[DRAW_HEIGHT][DRAW_WIDTH]) {
    const int center_y = DRAW_HEIGHT / 2; 
    const double y_scale = (double)center_y;

    for (int x = 0; x < DRAW_WIDTH; x++) {
        double y_val = samples[x];

        int y = (int)round(center_y + y_val * y_scale);

        if (y < 0) y = 0;
        if (y >= DRAW_HEIGHT) y = DRAW_HEIGHT - 1;

        buf[y][x] = DRAW_PLOT_CHAR;
    }
}

void draw_print_buffer(const char buf[DRAW_HEIGHT][DRAW_WIDTH]) {
    for (int y = 0; y < DRAW_HEIGHT; y++) {
        for (int x = 0; x < DRAW_WIDTH; x++) {
            putchar(buf[y][x]);
        }
        putchar('\n');
    }
}
