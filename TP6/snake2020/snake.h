#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_SIZE 4

typedef struct _coord {
    int x;
    int y;
    struct _coord *next;
} Coord;

enum direction{TOP, BOTTOM, LEFT, RIGHT};

struct _snake{
    Coord *segments_list;
    int size;
    enum direction dir;
};

typedef struct{
    struct _snake snake_body;
} Snake;


void add_segment(Snake *snake, int x, int y);
void crawl(Snake *snake, int nb_colonne, int nb_ligne);
void debug_snake(Snake snake);
int get_x_last_snake_part(Snake snake);
int get_y_last_snake_part(Snake snake);
void free_snake(Snake *snake);
Snake new_snake();

#endif
