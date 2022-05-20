#include<stdio.h>
#include<stdlib.h>

float *allocate_float_malloc_tab(int taille){
    float * tab = (float*) malloc(sizeof(float)*taille);
    return tab;
}


float *allocate_float_calloc_tab(int taille){
    float * tab = (float*) calloc(taille, sizeof(float));
    return tab;
}


void display_tab(float *tab , int taille){
    int i;
    for(i = 0; i < taille;  i++){
        printf("tab[%d]=%f\n", i, tab[i]);
    }
}


char *concat(char *tab1, char *tab2){
    int i, j, size_tab, save_i;
    char * concatenate_tab;
    size_tab = 0;
    for(i = 0; tab1[i] != '\0'; i++){
        size_tab = size_tab + 1;
    }
    for(i = 0; tab2[i] != '\0'; i++){
        size_tab = size_tab + 1;
    }
    concatenate_tab = (char *) malloc(sizeof(char)*size_tab + 1);
    for(i = 0; tab1[i] != '\0'; i++){
        concatenate_tab[i] = tab1[i];
        save_i = i+1;
    }
    for(j = save_i; tab2[j-save_i] != '\0'; j++){
        concatenate_tab[j] = tab2[j-save_i];
    }
    concatenate_tab[size_tab + 1] = '\0';
    return concatenate_tab;
}


int **alloue(int colonne, int ligne){
    int i;
    int **tab_int = (int **) malloc(sizeof(int)*colonne);
    for(i = 0; i < colonne; i++){
        tab_int[i] = (int *) malloc(sizeof(int)*ligne);
    }
    return tab_int;
}


void display_int(int **tab_int, int colonne , int ligne){
    int i, j;
    for(i = 0; i < colonne;  i++){
        for(j = 0; j < ligne; j++){
            printf("tab_int[%d][%d]=%d\n", i, j, tab_int[i][j]);
        }
    }
}


void libere(int** tab_int, int ligne){
    int i;
    for(i = 0; i < ligne; i++){
        free(tab_int[i]);
    }
    free(tab_int);
}


int main()
{
    int i;
    int **tab_int;
    float *tab_malloc;
    float *tab_calloc;
    char *tab_string;
    tab_malloc = allocate_float_malloc_tab(30);
    if(tab_malloc != NULL){
        printf("###### tab_malloc[] ######\n");
        display_tab(tab_malloc, 30);
        free(tab_malloc);
    }
    tab_calloc = allocate_float_calloc_tab(30);
    if(tab_calloc != NULL){
        printf("\n###### tab_calloc[] ######\n");
        display_tab(tab_calloc, 30);
        free(tab_calloc);
    }
    tab_string = concat("jeremy aime ", "les chiffres");
    if(tab_string != NULL){
        printf("\n###### tab_string[] ######\n");
        for(i = 0; tab_string[i] != '\0'; i++){
            printf("%c", tab_string[i]);
        }
    }
    free(tab_string);
    tab_int = alloue(2, 2);
    if(tab_int != NULL){
        printf("\n###### tab_string[][] ######\n");
        display_int(tab_int, 2, 2);
    }
    libere(tab_int, 2);
    return 0;
}