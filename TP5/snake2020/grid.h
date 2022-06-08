#ifndef GRID_H
#define GRID_H

#include"snake.h"

#define NBL 22
#define NBC 36

typedef struct {
    char** grid;
    int nbl;
    int nbc;
} Grid;
enum  Element{WALL = 'w', EMPTY = '-', FRUIT = 'f', SNAKE = 's'};
float compute_size(int h, int w);
void debug(Grid *struct_grid);
void draw_grid(Grid *struct_grid);
int get_grid(Grid *struct_grid, const char file_name[]);
enum Element move_snake(Grid *struct_grid, Snake *snake);
void place_snake(Grid *struct_grid, Snake *snake);
Grid* allocate_grid(int n, int m);
void free_grid(Grid *);

#endif