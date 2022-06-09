#ifndef GRID_H
#define GRID_H

#include"snake.h"

#define NBL 22
#define NBC 36

typedef struct {
    char** char_grid;
    int nbl;
    int nbc;
} Grid;
enum  Element{WALL = 'w', EMPTY = '-', FRUIT = 'f', SNAKE = 's'};
float compute_size(Grid * struct_grid, int h, int w);
void debug(Grid *struct_grid);
void draw_grid(Grid *struct_grid);
int get_grid(Grid *struct_grid, const char file_name[]);
void get_grid_size(Grid *struct_grid, const char file_name[]);
enum Element move_snake(Grid *struct_grid, Snake *snake);
void place_snake(Grid *struct_grid, Snake *snake);
Grid* allocate_grid(const char *file_name);
void free_grid(Grid *);

#endif