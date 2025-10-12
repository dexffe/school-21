#include "draw.h"
#include <stdio.h>
#include <math.h>

void draw_init_buffer(char buf[DRAW_HEIGHT][DRAW_WIDTH]){
    for (int y = 0; y < DRAW_HEIGHT; y++)
        for (int x = 0; x < DRAW_WIDTH; x++)
            buf[y][x] = DRAW_POINT_CHAR;
}

void draw_plot_samples(const double samples[DRAW_WIDTH], char buf[DRAW_HEIGHT][DRAW_WIDTH]){
    int row_center = (DRAW_HEIGHT - 1) / 2;
    for (int x = 0; x < DRAW_WIDTH; x++){
        int y = row_center - (int)round(samples[x] * (DRAW_HEIGHT/2.0));
        if (y < 0) y = 0;
        if (y >= DRAW_HEIGHT) y = DRAW_HEIGHT - 1;
        buf[y][x] = DRAW_PLOT_CHAR;
    }
}

void draw_print_buffer(const char buf[DRAW_HEIGHT][DRAW_WIDTH]){
    for (int y = 0; y < DRAW_HEIGHT; y++){
        for (int x = 0; x < DRAW_WIDTH; x++)
            putchar(buf[y][x]);
        putchar('\n');
    }
}
