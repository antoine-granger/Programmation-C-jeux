#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#include"grid.h"
#include"snake.h"

#define DIFFICULTY 6

const char* program_name;


void print_usage(FILE* stream, int exit_code){
    fprintf(stream, "Utilisation : %s options [fichierentrée ...]\n", program_name);
    fprintf(stream,"-h --help               Affiche ce message.\n"
                    " -i --input filename    prend une grille pour le jeu.\n"
                    " -v --verbose            Affiche des messages détaillés.\n");
    exit(exit_code);
}


int main(int argc, char* argv[]){
    Snake snake = {{{{1,3},{1,2},{1,1},{1,0}},LEFT}};
    enum Element element;
    Grid *struct_grid;
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE;
    int width = 640, height = 480;
    int next_option, nb_fruit, nb_move;
    /* Chaîne listant les lettres valides pour les options courtes. */
    const char* const short_options = "ho:v";
    /* Tableau décrivant les options longues valides. */
    const struct option long_options[] = {
            { "help",     0, NULL, 'h' },
            { "input", 1, NULL, 'i'},
            { "verbose", 0, NULL, 'v' },
            { NULL,       0, NULL, 0   }   /* Requis à la fin du tableau.  */
    };
    const char *input_filename = NULL;
/* Indique si l'on doit afficher les messages détaillés. */
    int verbose = 0;
/* Mémorise le nom du programme, afin de l'intégrer aux messages.
    Le nom est contenu dans argv[0]. */
    program_name = argv[0];
    do {
        next_option = getopt_long(argc, argv, short_options,
                                   long_options, NULL);
        switch(next_option)
        {
            case 'i': {   /* -i ou --input */
                input_filename = optarg;
                break;
            }
            case 'h': {   /* -h or --help */
                /* L'utilisateur a demandé l'aide-mémoire. L'affiche sur la sortie
                   standard et quitte avec le code de sortie 0 (fin normale). */
                print_usage(stdout, 0);
                break;
            }
            case 'v': {   /* -v ou --verbose */
                verbose = 1;
                break;
            }
            case '?': {   /* L'utilisateur a saisi une option invalide. */
                /* Affiche l'aide-mémoire sur le flux d'erreur et sort avec le code
                   de sortie un (indiquant une fin anormale). */
                print_usage(stderr, 1);
            }
            case -1: {    /* Fin des options.  */
                break;
            }
            default: {    /* Quelque chose d'autre : inattendu.  */
                abort();
            }
        }
    }
    while(next_option != -1);
/* Fin des options. OPTIND pointe vers le premier argument qui n'est pas une
    option. À des fins de démonstration, nous les affichons si l'option
    verbose est spécifiée. */
    if(verbose) {
        int i;
        for(i = optind; i < argc; ++i)
            printf("Argument : %s\n", argv[i]);
    }
    /* //// CODE PRINCIPAL //// */
    /* Ouverture de la fenêtre graphique */
    if(argc > 1){
        nb_fruit = get_grid(struct_grid, input_filename);
    }
    else{
        nb_fruit = get_grid(struct_grid, "01_grid.txt");
    }
    place_snake(struct_grid, &snake);
    MLV_create_window( "SNAKE", "3R-IN1B", width, height );
    MLV_change_frame_rate( 24);
    /* Ferme la fenêtre quand la touche ESC est enfoncé */
    nb_move = DIFFICULTY;
    while((MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE || touche != MLV_KEYBOARD_ESCAPE) && (nb_fruit > 0)) {
        MLV_clear_window(MLV_COLOR_BROWN);
        if(nb_move%DIFFICULTY == 0) {
            nb_move = 0;
            element = move_snake(struct_grid, &snake);
            if (element == FRUIT) {
                nb_fruit = nb_fruit - 1;
            }
            else if (element == WALL || element == SNAKE) {
                break;
            }
        }
        draw_grid(struct_grid);
        MLV_actualise_window();
        switch (touche) {
            case MLV_KEYBOARD_DOWN : {
                snake.snake_body.dir = BOTTOM;
                break;
            }
            case MLV_KEYBOARD_UP : {
                snake.snake_body.dir = TOP;
                break;
            }
            case MLV_KEYBOARD_LEFT : {
                snake.snake_body.dir = LEFT;
                break;
            }
            case MLV_KEYBOARD_RIGHT : {
                snake.snake_body.dir = RIGHT;
                break;
            }
            default:
                break;
        }
        touche = MLV_KEYBOARD_NONE;
        MLV_delay_according_to_frame_rate();
        nb_move = nb_move + 1;
    }
    MLV_free_window();
    return 0;
}
