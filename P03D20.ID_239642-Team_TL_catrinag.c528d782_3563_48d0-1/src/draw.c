#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "draw.h"
#include "eval.h"
#include "tokenize.h"
#include "validation.h"
#include "yard.h"

void draw_init_buffer(char buf[DRAW_HEIGHT][DRAW_WIDTH]) {
    for (int y = 0; y < DRAW_HEIGHT; y++) {
        for (int x = 0; x < DRAW_WIDTH; x++) {
            buf[y][x] = DRAW_POINT_CHAR;
        }
    }
}

int draw_map_y_to_screen(double y) {
    int screen_y = (int)round((y - Y_MIN) / (Y_MAX - Y_MIN) * (DRAW_HEIGHT - 1));
    
    if (screen_y < 0) screen_y = 0;
    if (screen_y >= DRAW_HEIGHT) screen_y = DRAW_HEIGHT - 1;
    
    return screen_y;
}
void draw_plot_samples(char buf[DRAW_HEIGHT][DRAW_WIDTH], const Token* postfix, int postfixCount) {
    for (int screen_x = 0; screen_x < DRAW_WIDTH; screen_x++) {
        double math_x = X_MIN + (double)screen_x / (DRAW_WIDTH - 1) * (X_MAX - X_MIN);
        
        double math_y = evaluatePostfix(postfix, postfixCount, math_x);
        
        if (isfinite(math_y) && math_y >= Y_MIN && math_y <= Y_MAX) {
            int screen_y = draw_map_y_to_screen(math_y);
            buf[screen_y][screen_x] = DRAW_PLOT_CHAR;
        }
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