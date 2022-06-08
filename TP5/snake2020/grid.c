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


void debug(Grid *struct_grid){
    int i,j;
    for(i = 0; i < NBL; i++){
        for(j = 0; j < NBC+1; j++){
            printf("%c", struct_grid->grid[i][j]);
        }
        printf("\n");
    }
}


void draw_grid(Grid *struct_grid){
    int i,j,h,w,x,y;
    float a;
    h = MLV_get_window_height();
    w = MLV_get_window_width();
    a = compute_size(h, w);
    for(i = 0; i < NBL; i++){
        for(j = 0; j < NBC+1; j++){
            y = a*i;
            x = a*j;
            if (struct_grid->grid[i][j]==WALL){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_BLACK);}
            else if  (struct_grid->grid[i][j]==FRUIT){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_RED);}
            else if (struct_grid->grid[i][j]==EMPTY){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_WHITE);}
            else if (struct_grid->grid[i][j]==SNAKE){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_GREEN2);}
            else{
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_GRAY);
            }
        }
    }
}


int get_grid(Grid *struct_grid, const char file_name[]){
    int i, j, nb_fruit;
    FILE* grid_file;
    char chara_in_file;
    grid_file = fopen(file_name, "r");
    i = 0;
    j = 0;
    nb_fruit = 0;
    if (grid_file != NULL) {
        while ((chara_in_file = fgetc(grid_file)) != EOF) {
            if(i == NBC+1){
                j = j + 1;
                i = 0;
            }
            if(j == NBL){
                break;
            }
            struct_grid->grid[j][i] = chara_in_file;
            if(chara_in_file == 'f'){
                nb_fruit = nb_fruit + 1;
            }
            i = i + 1;
        }
        fprintf(stderr, "\noui\n");
        fclose(grid_file);
    }
    return nb_fruit;
}


enum Element move_snake(Grid *struct_grid, Snake *snake){
    int x, y;
    enum Element element;
    /* efface la queue du serpent */
    x = snake->snake_body.snake_part[SNAKE_SIZE-1].x;
    y = snake->snake_body.snake_part[SNAKE_SIZE-1].y;
    struct_grid->grid[y][x] = EMPTY;
    /* deplace le serpent */
    crawl(snake);
    /* indique sur la grille la tête du serpent*/
    x = snake->snake_body.snake_part[0].x;
    y = snake->snake_body.snake_part[0].y;
    element = struct_grid->grid[y][x];
    struct_grid->grid[y][x] = SNAKE;
    return element;
}


void place_snake(Grid *struct_grid, Snake *snake){
    int x, y, part_snake;
    for(part_snake = 0; part_snake < SNAKE_SIZE; part_snake++){
        x = snake->snake_body.snake_part[part_snake].x;
        y = snake->snake_body.snake_part[part_snake].y;
        struct_grid->grid[y][x] = SNAKE;
    }
}

Grid* allocate_grid(int nbl, int nbc){
    Grid *struct_grid;
    char **grid;
    int i;
    struct_grid = (Grid *) malloc(sizeof(Grid));
    grid = (char **) malloc(sizeof(char)*nbc);
    for(i = 0; i < nbc; i++){
        grid[i] = (char *) malloc(sizeof(char)*nbl);
    }
    struct_grid->grid = grid;
    return struct_grid;
}


void free_grid(Grid *struct_grid){
    int i;
    for(i = 0; i < struct_grid->nbl; i++){
        free(struct_grid->grid[i]);
    }
    free(struct_grid);
}
