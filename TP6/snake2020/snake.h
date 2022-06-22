/*!
 * @file snake.h
 * @brief Header file of snake.c
 * @author Antoine.GRANGER
 * @date 22 June 2022
 */

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_SIZE 4

/*!@struct _Coord
 * @brief A part of the snake
 */
typedef struct _coord {
    int x;
    int y;
    struct _coord *next;
} Coord;

/*!
 * @enum direction
 * @brief Contains all the directions that the snake can take.
 */
enum direction{TOP, BOTTOM, LEFT, RIGHT};

/*!
 * @struct _snake
 * @brief the snake's structure
 */
struct _snake{
    Coord *segments_list; /*! Contains the position of each part from the snake */
    int size; /*! The size of the snake */
    enum direction dir; /*! The direction of the snake's next move */
};

/*!
 * @struct Snake
 * @brief contain a _snake structure
 */
typedef struct{
    struct _snake snake_body;
} Snake;


void add_segment(Snake *snake, int x, int y);
void crawl(Snake *snake, int nb_column, int nb_line);
void debug_snake(Snake snake);
int get_x_last_snake_part(Snake snake);
int get_y_last_snake_part(Snake snake);
void free_snake(Snake *snake);
Snake new_snake();

#endif
