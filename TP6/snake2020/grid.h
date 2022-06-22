/*!
 * @file grid.h
 * @brief Header file of grid.c
 * @author Antoine.GRANGER
 * @date 22 June 2022
 */

#ifndef GRID_H
#define GRID_H

#include"snake.h"

/*!
 * @typedef Grid
 * @brief The game's grid
 *
 */
typedef struct {
    char** char_grid; /*! A matrix which contain every value of the grid (Fruit / Wall / Snake / Empty)*/
    int nbl; /*! The number of lines in the game's grid*/
    int nbc; /*! The number of columns in the game's grid*/
} Grid;

/*!
 * @enum Element
 * @brief An enum of each possible value from the game's grid
 */
enum  Element{WALL = 'w', EMPTY = '-', FRUIT = 'f', SNAKE = 's'};
Grid* allocate_grid(const char *file_name);
float compute_size(Grid * struct_grid, int h, int w);
void debug(Grid *struct_grid);
void draw_grid(Grid *struct_grid);
void free_grid(Grid *);
int get_grid(Grid *struct_grid, const char file_name[]);
void get_grid_size(Grid *struct_grid, const char file_name[]);
enum Element move_snake(Grid *struct_grid, Snake *snake);
void place_snake(Grid *struct_grid, Snake snake);


#endif