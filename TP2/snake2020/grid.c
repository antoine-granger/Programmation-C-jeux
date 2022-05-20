#include<stdio.h>
#include <MLV/MLV_all.h>

#include"grid.h"

void debug(char matrice[][NBC+1]){
    int i,j;
    for(i = 0; i < NBL; i++){
        for(j = 0; j < NBC+1; j++){
            printf("%c", matrice[i][j]);
        }
        printf("\n");
    }
}


float compute_size(int h, int w){
    if(h <= w){
        return h/NBL;
    }
    return w/NBC;
}


void draw_grid(char matrice[][NBC+1]){
    int i,j,h,w,x,y;
    float a;
    h = MLV_get_window_height();
    w = MLV_get_window_width();
    a = compute_size(h, w);
    for(i = 0; i < NBL; i++){
        for(j = 0; j < NBC+1; j++){
            y = a*i;
            x = a*j;
            if (matrice[i][j]==WALL){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_BLACK);}
            else if  (matrice[i][j]==FRUIT){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_RED);}
            else if (matrice[i][j]==EMPTY){
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_WHITE);}
            else{
                MLV_draw_filled_rectangle(x, y, a, a, MLV_COLOR_GRAY);
            }
        }
    }
}
