#include<stdio.h>
#include<MLV/MLV_all.h>

#include"grid.h"
#include"snake.h"

float compute_size(Grid *struct_grid, int h, int w){
    if(h >= w){
        return h/(struct_grid->nbl);
    }
    return w/(struct_grid->nbc);
}


void debug(Grid *struct_grid){
    int i,j;
    for(i = 0; i < struct_grid->nbl; i++){
        for(j = 0; j < struct_grid->nbc; j++){
            printf("%c", struct_grid->char_grid[i][j]);
        }
        printf("\n");
    }
}


void draw_grid(Grid *struct_grid){
    int colonne,ligne,height,width,x,y;
    float dim_carre;
    height = MLV_get_window_height();
    width = MLV_get_window_width();
    dim_carre = compute_size(struct_grid, height, width);
    for(colonne = 0; colonne < struct_grid->nbl; colonne++){
        for(ligne = 0; ligne < struct_grid->nbc; ligne++){
            y = dim_carre*colonne;
            x = dim_carre*ligne;
            if (struct_grid->char_grid[colonne][ligne]==WALL){
                MLV_draw_filled_rectangle(x, y, dim_carre, dim_carre, MLV_COLOR_BLACK);}
            else if  (struct_grid->char_grid[colonne][ligne]==FRUIT){
                MLV_draw_filled_rectangle(x, y, dim_carre, dim_carre, MLV_COLOR_RED);}
            else if (struct_grid->char_grid[colonne][ligne]==EMPTY){
                MLV_draw_filled_rectangle(x, y, dim_carre, dim_carre, MLV_COLOR_WHITE);}
            else if (struct_grid->char_grid[colonne][ligne]==SNAKE){
                MLV_draw_filled_rectangle(x, y, dim_carre, dim_carre, MLV_COLOR_GREEN2);}
            else{
                MLV_draw_filled_rectangle(x, y, dim_carre, dim_carre, MLV_COLOR_GRAY);
            }
        }
    }
}


int get_grid(Grid *struct_grid, const char file_name[]){
    int colonne, ligne, nb_fruit;
    FILE* grid_file;
    char chara_in_file;
    grid_file = fopen(file_name, "r");
    colonne = 0, ligne = 0;
    nb_fruit = 0;
    if (grid_file != NULL) {
        while ((chara_in_file = fgetc(grid_file)) != EOF) {
            if(chara_in_file == '\n'){
                ligne = ligne + 1;
                colonne = 0;
                continue;
            }
            struct_grid->char_grid[ligne][colonne] = chara_in_file;
            if(chara_in_file == 'f'){
                nb_fruit = nb_fruit + 1;
            }
            colonne = colonne + 1;
        }
        fclose(grid_file);
    }
    return nb_fruit;
}


void get_grid_size(Grid *struct_grid, const char *file_name){
    int colonne, ligne;
    FILE* grid_file;
    char chara_in_file;
    grid_file = fopen(file_name, "r");
    colonne = 0, ligne = 0;
    if (grid_file != NULL) {
        /* arrive au bout du fichier */
        while ((chara_in_file = fgetc(grid_file)) != EOF) {
            /* arrive en bout de ligne */
            if(chara_in_file == '\n'){
                ligne = ligne + 1;
                colonne = 0;
                continue;
            }
            colonne = colonne + 1;
        }
        /* pour le cas ou il n'y a pas de saut de ligne mais une fin de chaine */
        ligne = ligne + 1;
        fclose(grid_file);
    }
    struct_grid->nbl = ligne;
    struct_grid->nbc = colonne;
}


enum Element move_snake(Grid *struct_grid, Snake *snake){
    int x, y;
    enum Element element;
    /* efface la queue du serpent */
    x = snake->snake_body.snake_part[SNAKE_SIZE-1].x;
    y = snake->snake_body.snake_part[SNAKE_SIZE-1].y;
    struct_grid->char_grid[y][x] = EMPTY;
    /* deplace le serpent */
    crawl(snake);
    /* indique sur la grille la tête du serpent*/
    x = snake->snake_body.snake_part[0].x;
    y = snake->snake_body.snake_part[0].y;
    element = struct_grid->char_grid[y][x];
    struct_grid->char_grid[y][x] = SNAKE;
    return element;
}


void place_snake(Grid *struct_grid, Snake *snake){
    int x, y, part_snake;
    for(part_snake = 0; part_snake < SNAKE_SIZE; part_snake++){
        x = snake->snake_body.snake_part[part_snake].x;
        y = snake->snake_body.snake_part[part_snake].y;
        struct_grid->char_grid[y][x] = SNAKE;
    }
}

Grid* allocate_grid(const char file_name[]){
    int ligne;
    Grid *struct_grid;
    struct_grid = (Grid *) malloc(sizeof(Grid));
    if(struct_grid != NULL) {
        get_grid_size(struct_grid, file_name);
        struct_grid->char_grid = (char **) malloc(sizeof(char *) * (struct_grid->nbl));
        for (ligne = 0; ligne < struct_grid->nbl+1; ligne++){
            struct_grid->char_grid[ligne] = (char *) malloc(sizeof(char) * (struct_grid->nbc));
        }
        if (struct_grid->char_grid != NULL) {
            return struct_grid;
        }
    }
    return struct_grid;
}


void free_grid(Grid *struct_grid){
    int i;
    for(i = 0; i < struct_grid->nbl; i++){
        free(struct_grid->char_grid[i]);
    }
    free(struct_grid);
}
