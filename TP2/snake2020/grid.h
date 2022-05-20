#ifndef GRID_H
#define GRID_H

#define NBL 22
#define NBC 36

enum  Element{WALL = 'w', EMPTY = ' ', FRUIT = 'f'};
void debug(char matrice[][NBC+1]);
float compute_size(int h, int w);
void draw_grid(char matrice[][NBC+1]);

#endif