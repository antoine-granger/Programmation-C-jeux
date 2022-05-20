#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include"grid.h"
#include"snake.h"


const char* program_name;


void print_usage(FILE* stream, int exit_code)
{
    fprintf(stream, "Utilisation : %s options [fichierentrée ...]\n", program_name);
    fprintf(stream,"-h --help               Affiche ce message.\n"
                    " -o --output filename    Redirige la sortie vers un fichier.\n"
                    " -v --verbose            Affiche des messages détaillés.\n");
    exit(exit_code);
}


int main(int argc, char* argv[]){
    Snake snake = {{{{1,3},{1,2},{1,1},{1,0}},LEFT}};
    char grid[NBL][NBC+1] = {
            "w                                  w",
            "                                    ",
            "               f                    ",
            "                                    ",
            "     f               f              ",
            "                                    ",
            "                                    ",
            "               f                    ",
            "                                    ",
            "                                    ",
            "         wwwwwwwwww                 ",
            "                                    ",
            "                                    ",
            "                                    ",
            "                                    ",
            "                                    ",
            "                  f                 ",
            "                                    ",
            "         f                f         ",
            "                                    ",
            "                 f                  ",
            "w                                  w"
    };
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE;
    int width = 640, height = 480;
    int next_option;
    /* Chaîne listant les lettres valides pour les options courtes. */
    const char* const short_options = "ho:v";
    /* Tableau décrivant les options longues valides. */
    const struct option long_options[] = {
            { "help",     0, NULL, 'h' },
            { "output",   1, NULL, 'o' },
            { "verbose", 0, NULL, 'v' },
            { NULL,       0, NULL, 0   }   /* Requis à la fin du tableau.  */
    };
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
    place_snake(grid, &snake);
    MLV_create_window( "SNAKE", "3R-IN1B", width, height );
    MLV_change_frame_rate( 10);
    /* Ferme la fenêtre quand la touche ESC est enfoncé */
    while(MLV_get_event(&touche, NULL, NULL,NULL, NULL,NULL,
                        NULL, NULL,NULL) == MLV_NONE || touche != MLV_KEYBOARD_ESCAPE){
        MLV_clear_window( MLV_COLOR_BROWN );
        draw_grid(grid);
        MLV_actualise_window();
        touche = MLV_KEYBOARD_NONE;
        MLV_delay_according_to_frame_rate();
        move_snake(grid, &snake);
    }
    MLV_free_window();
    return 0;
}
