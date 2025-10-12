#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include "tokenize.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DRAW_HEIGHT 25
#define DRAW_WIDTH 80
#define DRAW_POINT_CHAR '.'
#define DRAW_PLOT_CHAR '*'
#define X_MIN 0.0
#define X_MAX (4.0 * M_PI)
#define Y_MIN -1.0
#define Y_MAX 1.0

void draw_init_buffer(char buf[DRAW_HEIGHT][DRAW_WIDTH]);
int draw_map_y_to_screen(double y);
void draw_plot_samples(char buf[DRAW_HEIGHT][DRAW_WIDTH], Token* postfix, int postfixCount);
void draw_print_buffer(const char buf[DRAW_HEIGHT][DRAW_WIDTH]);

#endif