#include"grid.h"
#include "snake.h"
#include<stdio.h>
#include <MLV/MLV_all.h>


void crawl(Snake *snake){
    int i, x_head, y_head, x_next_pos_head, y_next_pos_head;
    x_head = snake->snake_body.snake_part[0].x;
    y_head = snake->snake_body.snake_part[0].y;
    switch(snake->snake_body.dir){
        case LEFT:{
            x_next_pos_head = (x_head-1+NBC) % NBC;
            y_next_pos_head = y_head;
            break;
        }
        case RIGHT:{
            x_next_pos_head = (x_head+1) % NBC;
            y_next_pos_head = y_head;
            break;
        }
        case TOP: {
            x_next_pos_head = x_head;
            y_next_pos_head = (y_head-1+NBL) % NBL;;
            break;
        }
        case BOTTOM: {
            x_next_pos_head = x_head;
            y_next_pos_head = (y_head+1) % NBL;
            break;
        }
        default: {   /* Quelque chose d'autre : inattendu.  */
            abort();
        }
    }
    for(i = SNAKE_SIZE-1; i > 0; i--){
        snake->snake_body.snake_part[i].x = snake->snake_body.snake_part[i-1].x;
        snake->snake_body.snake_part[i].y = snake->snake_body.snake_part[i-1].y;
    }
    snake->snake_body.snake_part[0].x = x_next_pos_head;
    snake->snake_body.snake_part[0].y = y_next_pos_head;
}
