#include"grid.h"
#include "snake.h"

#include <MLV/MLV_all.h>


void crawl(Snake *snake, int nb_colonne, int nb_ligne){
    int x_head, y_head, x_head_save, y_head_save, x_next_pos_head, y_next_pos_head;
    Coord *snake_part_tmp = snake[0].snake_body.segments_list;
    x_head = snake[0].snake_body.segments_list->x;
    y_head = snake[0].snake_body.segments_list->y;
    switch(snake[0].snake_body.dir){
        case LEFT:{
            x_next_pos_head = (x_head-1+nb_colonne) % nb_colonne;
            y_next_pos_head = y_head;
            break;
        }
        case RIGHT:{
            x_next_pos_head = (x_head+1) % nb_colonne;
            y_next_pos_head = y_head;
            break;
        }
        case TOP: {
            x_next_pos_head = x_head;
            y_next_pos_head = (y_head-1+nb_ligne) % nb_ligne;;
            break;
        }
        case BOTTOM: {
            x_next_pos_head = x_head;
            y_next_pos_head = (y_head+1) % nb_ligne;
            break;
        }
        default: {   /* Quelque chose d'autre : inattendu.  */
            abort();
        }
    }
    while(snake_part_tmp->next != NULL){
        snake_part_tmp = snake_part_tmp->next;
        x_head_save = snake_part_tmp->x;
        y_head_save = snake_part_tmp->y;
        snake_part_tmp->x = x_head;
        snake_part_tmp->y = y_head;
        x_head = x_head_save;
        y_head = y_head_save;
    }
    snake[0].snake_body.segments_list->x = x_next_pos_head;
    snake[0].snake_body.segments_list->y = y_next_pos_head;
}


Snake new_snake(){
    Snake snake;
    snake.snake_body.size = 0;
    snake.snake_body.segments_list = (Coord *) malloc(sizeof(Coord));;
    snake.snake_body.dir = RIGHT;
    return snake;
}


int get_x_last_snake_part(Snake snake){
    while(snake.snake_body.segments_list->next != NULL){
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    return snake.snake_body.segments_list->x;
}


int get_y_last_snake_part(Snake snake){
    while(snake.snake_body.segments_list->next != NULL){
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    return snake.snake_body.segments_list->y;
}


void add_segment(Snake *snake, int x, int y){
    Coord *new_snake_part = malloc(sizeof(Coord));
    if(new_snake_part != NULL){
        new_snake_part->next = NULL;
        new_snake_part->x = x;
        new_snake_part->y = y;
        if (snake[0].snake_body.size == 0) {
            snake[0].snake_body.segments_list = new_snake_part;
        }
        else{
            Coord *snake_part_tmp = snake[0].snake_body.segments_list;
            while (snake_part_tmp->next != NULL){
                snake_part_tmp = snake_part_tmp->next;
            }
            snake_part_tmp->next = new_snake_part;
        }
        snake[0].snake_body.size += 1;
    }
}


void debug_snake(Snake snake){
    while(snake.snake_body.segments_list->next != NULL){
        fprintf(stderr, "\nx=%d, y=%d", snake.snake_body.segments_list->x, snake.snake_body.segments_list->y);
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    fprintf(stderr, "\nx=%d, y=%d\n", snake.snake_body.segments_list->x, snake.snake_body.segments_list->y);
}


void free_snake(Snake *snake){
    Snake save_snake;
    while(snake[0].snake_body.segments_list != NULL){
        save_snake.snake_body.segments_list = snake[0].snake_body.segments_list->next;
        free(snake[0].snake_body.segments_list);
        snake[0] = save_snake;
    }
}
