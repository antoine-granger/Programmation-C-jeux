#include<stdio.h>
#include<MLV/MLV_all.h>

#include"grid.h"
#include"snake.h"

float compute_size(int h, int w){
    if(h >= w){
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


void get_grid(char grid[][NBC+1], const char file_name[]){
    int i, j;
    FILE* grid_file;
    char chara_in_file;
    grid_file = fopen(file_name, "r");
    i = 0;
    j = 0;
    if (grid_file != NULL) {
        while ((chara_in_file = fgetc(grid_file)) != EOF) {
            if (i == NBC+1){
                j = j + 1;
                i = 0;
            }
            if(j == NBL){
                break;
            }
            grid[j][i] = chara_in_file;
            printf("%c", grid[j][i]);
            i = i + 1;
        }
        fclose(grid_file);
    }
}


enum Element move_snake(char grille[][NBC+1], Snake *snake){
    int x, y;
    enum Element element;
    /* efface la queue du serpent */
    x = snake->snake_body.snake_part[SNAKE_SIZE-1].x;
    y = snake->snake_body.snake_part[SNAKE_SIZE-1].y;
    grille[y][x] = EMPTY;
    /* deplace le serpent */
    crawl(snake);
    grille[y][x] = SNAKE;
    /* indique sur la grille la tête du serpent*/
    x = snake->snake_body.snake_part[0].x;
    y = snake->snake_body.snake_part[0].y;
    element = grille[y][x];
    return element;
}


void place_snake(char grille[][NBC+1], Snake *snake){
    int x, y, part_snake;
    for(part_snake = 0; part_snake < SNAKE_SIZE; part_snake++){
        x = snake->snake_body.snake_part[part_snake].x;
        y = snake->snake_body.snake_part[part_snake].y;
        grille[y][x] = SNAKE;
    }
}