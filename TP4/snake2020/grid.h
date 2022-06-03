#ifndef GRID_H
#define GRID_H

#include"snake.h"

#define NBL 22
#define NBC 36

enum  Element{WALL = 'w', EMPTY = '-', FRUIT = 'f', SNAKE = 's'};
float compute_size(int h, int w);
void debug(char matrice[][NBC+1]);
void draw_grid(char matrice[][NBC+1]);
int get_grid(char grille[][NBC+1], const char file_name[]);
enum Element move_snake(char grille[][NBC+1], Snake *snake);
void place_snake(char matrice[][NBC+1], Snake *snake);

#endif