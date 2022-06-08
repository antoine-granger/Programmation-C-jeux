#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_SIZE 4

typedef struct{
    int x;
    int y;
} Coord;

enum direction{TOP, BOTTOM, LEFT, RIGHT};

struct _snake{
    Coord snake_part[SNAKE_SIZE];
    enum direction dir;
};

typedef struct{
    struct _snake snake_body;
} Snake;


void crawl(Snake *snake);

#endif
