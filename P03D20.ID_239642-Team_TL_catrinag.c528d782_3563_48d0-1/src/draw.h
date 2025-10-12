#ifndef DRAW_H

#define DRAW_WIDTH 80
#define DRAW_HEIGHT 25
#define DRAW_POINT_CHAR '.'
#define DRAW_PLOT_CHAR '*'

void draw_init_buffer(char buf[DRAW_HEIGHT][DRAW_WIDTH]);
void draw_plot_samples(const double samples[DRAW_WIDTH], char buf[DRAW_HEIGHT][DRAW_WIDTH]);
void draw_print_buffer(const char buf[DRAW_HEIGHT][DRAW_WIDTH]);

#endif