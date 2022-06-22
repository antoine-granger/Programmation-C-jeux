/*!@file grid.c
 * @brief Contains all the functions that declare, initialize, modify the game's grid
 * @author Antoine.GRANGER
 * @date 22 June 2022
 */
#include<stdio.h>
#include<MLV/MLV_all.h>

#include"grid.h"
#include"snake.h"


/*!
 * @fn float compute_size(Grid *struct_grid, int h, int w)
 * @brief Calculates the size of the squares displayed on the screen to fit the size of the window
 *
 * @param struct_grid the game's grid
 * @param h Height of the window
 * @param w Width of the window
 * @return Gives the length of the sides of each square of the grid
 */
float compute_size(Grid *struct_grid, int h, int w){
    float ll;
    ll = h / (struct_grid->nbl);
    if (ll*struct_grid->nbc< w) {
        return (float) h / (struct_grid->nbl);
    }
    return (float) w / (struct_grid->nbc);
}

/*!
 * @fn void debug(Grid *struct_grid)
 * @brief Displays the grid in the terminal
 *
 * @param struct_grid The game's grid
 */
void debug(Grid *struct_grid){
    int i,j;
    for(i = 0; i < struct_grid->nbl; i++){
        for(j = 0; j < struct_grid->nbc; j++){
            printf("%c", struct_grid->char_grid[i][j]);
        }
        printf("\n");
    }
}

/*!
 * @fn void draw_grid(Grid *struct_grid)
 * @brief Draw the grid in a window with the MLV library
 *
 * @param struct_grid The game's grid
 */
void draw_grid(Grid *struct_grid){
    int column,line, height, width;
    float dim_square, x, y;
    height = MLV_get_window_height();
    width = MLV_get_window_width();
    dim_square = compute_size(struct_grid, height, width);
    for(column = 0; column < struct_grid->nbl; column++){
        for(line = 0; line < struct_grid->nbc; line++){
            y = (float) dim_square*column;
            x = (float) dim_square*line;
            if (struct_grid->char_grid[column][line]==WALL){
                MLV_draw_filled_rectangle(x, y, dim_square, dim_square, MLV_COLOR_BLACK);}
            else if  (struct_grid->char_grid[column][line]==FRUIT){
                MLV_draw_filled_rectangle(x, y, dim_square, dim_square, MLV_COLOR_RED);}
            else if (struct_grid->char_grid[column][line]==EMPTY){
                MLV_draw_filled_rectangle(x, y, dim_square, dim_square, MLV_COLOR_WHITE);}
            else if (struct_grid->char_grid[column][line]==SNAKE){
                MLV_draw_filled_rectangle(x, y, dim_square, dim_square, MLV_COLOR_GREEN2);}
            else{
                MLV_draw_filled_rectangle(x, y, dim_square, dim_square, MLV_COLOR_GRAY);
            }
        }
    }
}

/*!
 * @fn int get_grid(Grid *struct_grid, const char file_name[])
 * @brief Retrieves the level contained in the file whose name is passed in parameter, stores it in the game's grid and
 * returns the number of fruits present in this level
 *
 * @param struct_grid The game's grid
 * @param file_name The name of the level file
 * @return Gives the number of fruit present in the game's grid
 */
int get_grid(Grid *struct_grid, const char file_name[]){
    int column, line, nb_fruit;
    FILE* grid_file;
    char chara_in_file;
    grid_file = fopen(file_name, "r");
    column = 0, line = 0;
    nb_fruit = 0;
    if (grid_file != NULL) {
        while ((chara_in_file = fgetc(grid_file)) != EOF) {
            if(chara_in_file == '\n'){
                line = line + 1;
                column = 0;
                continue;
            }
            struct_grid->char_grid[line][column] = chara_in_file;
            if(chara_in_file == 'f'){
                nb_fruit = nb_fruit + 1;
            }
            column = column + 1;
        }
        fclose(grid_file);
    }
    return nb_fruit;
}

/*!
 * @fn void get_grid_size(Grid *struct_grid, const char *file_name)
 * @brief Initializes parameter nbc and nbl in the game's grid
 * (indicate the number of column and line in the game's grid)
 *
 * @param struct_grid The game's grid
 * @param file_name The name of the level file
 */
void get_grid_size(Grid *struct_grid, const char *file_name){
    int column, line;
    FILE* grid_file;
    char chara_in_file;
    grid_file = fopen(file_name, "r");
    column = 0, line = 0;
    if (grid_file != NULL) {
        /* reaches the end of the file */
        while ((chara_in_file = fgetc(grid_file)) != EOF) {
            /* arrives at the end of the line */
            if(chara_in_file == '\n'){
                line = line + 1;
                column = 0;
                continue;
            }
            column = column + 1;
        }
        /* for the case where there is no line break but an end of string */
        line = line + 1;
        fclose(grid_file);
    }
    /* initialize the nbc and nbl parameter in the game's grid */
    struct_grid->nbl = line;
    struct_grid->nbc = column;
}

/*!
 * @fn enum Element move_snake(Grid *struct_grid, Snake *snake)
 * @brief Move the snake on the grid by erasing the snake's tail, moving his head and by moving each part of his body
 *
 * @param struct_grid The game's grid
 * @param snake The game's snake
 * @return Gives the value of the square on which the snake's head has arrived
 */
enum Element move_snake(Grid *struct_grid, Snake *snake){
    int x, y;
    enum Element element;
    Coord *snake_part_tmp = snake[0].snake_body.segments_list;
    /* remove the snake tail */
    while (snake_part_tmp->next != NULL) {
        snake_part_tmp = snake_part_tmp->next;
    }
    x = snake_part_tmp->x;
    y = snake_part_tmp->y;
    struct_grid->char_grid[y][x] = EMPTY;
    /* shifts all parts of the snake towards its head */
    crawl(snake, struct_grid->nbc, struct_grid->nbl);
    /* place the snake's head on the grid */
    x = snake[0].snake_body.segments_list->x;
    y = snake[0].snake_body.segments_list->y;
    element = struct_grid->char_grid[y][x];
    struct_grid->char_grid[y][x] = SNAKE;
    return element;
}

/*!
 * @fn void place_snake(Grid *struct_grid, Snake snake)
 * @brief Place the snake on the game's grid
 *
 * @param struct_grid The game's grid
 * @param snake The game's snake
 */
void place_snake(Grid *struct_grid, Snake snake){
    int x, y;
    /* place each part of the snake on the game's grid */
    while (snake.snake_body.segments_list->next != NULL){
        x = snake.snake_body.segments_list->x;
        y = snake.snake_body.segments_list->y;
        struct_grid->char_grid[y][x] = SNAKE;
        snake.snake_body.segments_list = snake.snake_body.segments_list->next;
    }
    x = snake.snake_body.segments_list->x;
    y = snake.snake_body.segments_list->y;
    struct_grid->char_grid[y][x] = SNAKE;
}

/*!
 * @fn Grid* allocate_grid(const char file_name[])
 * @def Allocate the good size of the game's grid in the memory
 *
 * @param file_name The name of the level file
 * @return Gives the game's grid with is allocation
 */
Grid* allocate_grid(const char file_name[]){
    int line;
    Grid *struct_grid;
    struct_grid = (Grid *) malloc(sizeof(Grid));
    if(struct_grid != NULL) {
        get_grid_size(struct_grid, file_name);
        struct_grid->char_grid = (char **) malloc(sizeof(char *) * (struct_grid->nbl));
        for (line = 0; line < struct_grid->nbl+1; line++){
            struct_grid->char_grid[line] = (char *) malloc(sizeof(char) * (struct_grid->nbc));
        }
        if (struct_grid->char_grid != NULL) {
            return struct_grid;
        }
    }
    return struct_grid;
}

/*!
 * @fn void free_grid(Grid *struct_grid)
 * @brief Frees the memory allocated by the game's grid
 *
 * @param struct_grid The game's grid
 */
void free_grid(Grid *struct_grid){
    int i;
    for(i = 0; i < struct_grid->nbl; i++){
        free(struct_grid->char_grid[i]);
    }
    free(struct_grid);
}
