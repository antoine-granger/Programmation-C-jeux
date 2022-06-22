/*!@file snake.c
 * @brief Contains all the functions that declare, initialize, modify the snake
 * @author Antoine.GRANGER
 * @date 22 June 2022
 */
#include "snake.h"

#include <MLV/MLV_all.h>

/*!
 * @fn void crawl(Snake *snake, int nb_column, int nb_line)
 * @brief Shifts all parts of the snake towards its head
 *
 * @param snake The game's snake
 * @param nb_column The number of columns in the game's grid
 * @param nb_line The number of lines in the game's grid
 */
void crawl(Snake *snake, int nb_column, int nb_line){
    int x_head, y_head, x_head_save, y_head_save, x_next_pos_head, y_next_pos_head;
    Coord *snake_part_tmp = snake[0].snake_body.segments_list;
    x_head = snake[0].snake_body.segments_list->x;
    y_head = snake[0].snake_body.segments_list->y;
    switch(snake[0].snake_body.dir){
        case LEFT:{
            x_next_pos_head = (x_head-1+nb_column) % nb_column;
            y_next_pos_head = y_head;
            break;
        }
        case RIGHT:{
            x_next_pos_head = (x_head+1) % nb_column;
            y_next_pos_head = y_head;
            break;
        }
        case TOP: {
            x_next_pos_head = x_head;
            y_next_pos_head = (y_head-1+nb_line) % nb_line;
            break;
        }
        case BOTTOM: {
            x_next_pos_head = x_head;
            y_next_pos_head = (y_head+1) % nb_line;
            break;
        }
        default: {   /* Something else: unexpected. */
            abort();
        }
    }
    /* Shifts all parts of the snake towards its head */
    while(snake_part_tmp->next != NULL){
        snake_part_tmp = snake_part_tmp->next;
        x_head_save = snake_part_tmp->x;
        y_head_save = snake_part_tmp->y;
        snake_part_tmp->x = x_head;
        snake_part_tmp->y = y_head;
        x_head = x_head_save;
        y_head = y_head_save;
    }
    /* Change the head position X and Y */
    snake[0].snake_body.segments_list->x = x_next_pos_head;
    snake[0].snake_body.segments_list->y = y_next_pos_head;
}

/*!
 * @fn Snake new_snake()
 * @brief Allocate a snake in memory
 *
 * @return Gives a snake allocate dynamically in memory
 */
Snake new_snake(){
    Snake snake;
    snake.snake_body.size = 0;
    snake.snake_body.segments_list = (Coord *) malloc(sizeof(Coord));
    snake.snake_body.dir = RIGHT;
    return snake;
}

/*!
 * @fn int get_x_last_snake_part(Snake snake)
 * @brief gives the X position of the snake's tail
 *
 * @param snake The game's snake
 * @return The X position of the snake's tail
 */
int get_x_last_snake_part(Snake snake){
    while(snake.snake_body.segments_list->next != NULL){
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    return snake.snake_body.segments_list->x;
}

/*!
 * @fn int get_y_last_snake_part(Snake snake)
 * @brief gives the X position of the snake's tail
 *
 * @param snake The game's snake
 * @return The Y position of the snake's tail
 */
int get_y_last_snake_part(Snake snake){
    while(snake.snake_body.segments_list->next != NULL){
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    return snake.snake_body.segments_list->y;
}

/*!
 * @fn void add_segment(Snake *snake, int x, int y)
 * @brief add a snake part on the game's snake
 *
 * @param snake The game's snake
 * @param x The X position of the new snake part
 * @param y The Y position of the new snake part
 */
void add_segment(Snake *snake, int x, int y){
    Coord *new_snake_part = malloc(sizeof(Coord));
    /* If the new snake part has been allocated well */
    if(new_snake_part != NULL){
        new_snake_part->next = NULL;
        new_snake_part->x = x;
        new_snake_part->y = y;
        /* If the snake has no head */
        if (snake[0].snake_body.size == 0) {
            snake[0].snake_body.segments_list = new_snake_part;
        }
        else{
            Coord *snake_part_tmp = snake[0].snake_body.segments_list;
            /* Add the new part at the end of the list */
            while (snake_part_tmp->next != NULL){
                snake_part_tmp = snake_part_tmp->next;
            }
            snake_part_tmp->next = new_snake_part;
        }
        /* Increment the snake's size */
        snake[0].snake_body.size += 1;
    }
}

/*!
 * @fn void debug_snake(Snake snake)
 * @brief Display all the snake part position X and Y
 *
 * @param snake The game's snake
 */
void debug_snake(Snake snake){
    /* Print all X and Y positions of the snake part */
    while(snake.snake_body.segments_list->next != NULL){
        fprintf(stderr, "\nx=%d, y=%d", snake.snake_body.segments_list->x, snake.snake_body.segments_list->y);
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    fprintf(stderr, "\nx=%d, y=%d\n", snake.snake_body.segments_list->x, snake.snake_body.segments_list->y);
}

/*!
 * @fn void free_grid(Grid *struct_grid)
 * @brief Frees the memory allocated by the game's snake
 *
 * @param struct_grid The game's snake
 */
void free_snake(Snake *snake){
    Snake save_snake;
    while(snake[0].snake_body.segments_list != NULL){
        save_snake.snake_body.segments_list = snake[0].snake_body.segments_list->next;
        free(snake[0].snake_body.segments_list);
        snake[0] = save_snake;
    }
}
