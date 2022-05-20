#include<stdio.h>
#include<MLV/MLV_all.h>

#include"grid.h"
#include"snake.h"

float compute_size(int h, int w){
    if(h <= w){
        return h/NBL;
    }
    return w/NBC;
}


void debug(char grille[][NBC+1]){
    int i,j;
    for(i = 0; i < NBL; i++){
        for(j = 0; j < NBC+1; j++){
            printf("%c", grille[i][j]);
        }
        printf("\n");
    }
}


void draw_grid(char grille[][NBC+1]){
    int i,j,h,w,x,y;
    float a;
    h = MLV_get_window_height();
    w = MLV_get_window_width();
    a = compute_size(h, w);
    for(i = 0; i < NBL; i++){
        for(j = 0; j < NBC+1; j++){
            y = a*i;
            x = a*j;
            if (grille[i][j]==WALL){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_BLACK);}
            else if  (grille[i][j]==FRUIT){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_RED);}
            else if (grille[i][j]==EMPTY){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_WHITE);}
            else if (grille[i][j]==SNAKE){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_GREEN2);}
            else{
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_GRAY);
            }
        }
    }
}


void move_snake(char grille[][NBC+1], Snake *snake){
    int x, y;
    /* efface la queue du serpent */
    x = snake->snake_body.snake_part[SNAKE_SIZE-1].x;
    y = snake->snake_body.snake_part[SNAKE_SIZE-1].y;
    grille[y][x] = EMPTY;
    /* deplace le serpent */
    crawl(snake);
    /* indique sur la grille la tête du serpent*/
    x = snake->snake_body.snake_part[0].x;
    y = snake->snake_body.snake_part[0].y;
    printf("\nposition x de la tête du serpent : %d", x);
    printf("\nposition y de la tête du serpent : %d", y);
    grille[y][x] = SNAKE;
}


void place_snake(char grille[][NBC+1], Snake *snake){
    int x, y, part_snake;
    for(part_snake = 0; part_snake < SNAKE_SIZE; part_snake++){
        x = snake->snake_body.snake_part[part_snake].x;
        y = snake->snake_body.snake_part[part_snake].y;
        grille[y][x] = SNAKE;
        printf("\n(x = %d y = %d)",x,y);
    }
}