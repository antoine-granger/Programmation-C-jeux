/*!
 * @file game.c
 * @brief Contains the main
 * @author Antoine.GRANGER
 * @date 22 June 2022
 */
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <unistd.h>
#include"grid.h"
#include"snake.h"


#define DIFFICULTY 6

const char* program_name;

/*!
 * @fn void print_usage(FILE* stream, int exit_code)
 * @param stream
 * @param exit_code
 */
void print_usage(FILE* stream, int exit_code){
    fprintf(stream, "Utilisation : %s options [fichierentrée ...]\n", program_name);
    fprintf(stream,"-h --help               Affiche ce message.\n"
                    " -i --input filename    The filename of the game's level.\n"
                    " -v --verbose            Affiche des messages détaillés.\n");
    exit(exit_code);
}

/*!
 * @fn int main(int argc, char* argv[])
 * @brief the main
 *
 * It is the main file of our snake game
 *
 * @param argc Contain the number of argument given when launching the game
 * @param argv Contain the arguments given when launching the game
 */
int main(int argc, char* argv[]){
    int width , height, next_option, nb_fruit, nb_move , verbose;
    enum Element element;
    Grid *struct_grid;
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE;
    Snake snake;
    const char* const short_options = "ho:v";

    /* Table describing the valid long options. */
    const struct option long_options[] = {
            { "help",     0, NULL, 'h' },
            { "input", 1, NULL, 'i'},
            { "verbose", 0, NULL, 'v' },
            { NULL,       0, NULL, 0   }   /* Requis à la fin du tableau.  */
    };
    const char *input_filename = NULL;
    width = 640, height = 480;
    /* Indicates whether to display detailed messages. */
    verbose = 0;
    /* Stores the name of the program, in order to integrate it in the messages.
    The name is contained in argv[0]. */
    program_name = argv[0];
    do {
        next_option = getopt_long(argc, argv, short_options,
                                   long_options, NULL);
        switch(next_option)
        {
            case 'i': {   /* -i or --input */
                input_filename = optarg;
                break;
            }
            case 'h': {   /* -h or --help */
                /* The user has requested the reminder. Displays it on the standard output
                   and exits with exit code 0 (normal end). */
                print_usage(stdout, 0);
                break;
            }
            case 'v': {   /* -v or --verbose */
                verbose = 1;
                break;
            }
            case '?': {   /* The user has entered an invalid option. */
                /* Displays the error flow reminder and exits with exit code code one
                   (indicating an abnormal termination). */
                print_usage(stderr, 1);
            }
            case -1: {    /* End of the options.  */
                break;
            }
            default: {    /* Something else: unexpected. */
                abort();
            }
        }
    }
    while(next_option != -1);
    /*
       End of options. OPTIND points to the first argument which is not an option.
       For demonstration purposes, we display them if the
       verbose option is specified.
    */
    if(verbose) {
        int i;
        for(i = optind; i < argc; ++i)
            printf("Argument : %s\n", argv[i]);
    }
    /* //// MAIN CODE BEGINNING //// */
    /* Opening the graphic window */
    if(argc == 1) {
        input_filename = "levels/default_grid.txt";
    }
    /* Create the game's snake */
    snake = new_snake();
    add_segment(&snake, 2, 1);
    add_segment(&snake, 2, 2);
    add_segment(&snake, 1, 2);
    add_segment(&snake, 1, 1);
    /* Create the game's grid */
    struct_grid = allocate_grid(input_filename);
    nb_fruit = get_grid(struct_grid, input_filename);
    /* Place the snake in the game's grid and create the game's window */
    place_snake(struct_grid, snake);
    MLV_create_window( "SNAKE", "3R-IN1B", width, height );
    MLV_change_frame_rate( 24);
    /* Closes the window when the ESC key is pressed */
    nb_move = DIFFICULTY;
    /* Does not stop until the snake has reached a part of the snake, a wall or has eaten all the fruits of the level */
    while(MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE || touche != MLV_KEYBOARD_ESCAPE) {
        MLV_clear_window(MLV_COLOR_BROWN);
        /* Change the speed of the snake */
        if(nb_move%DIFFICULTY == 0) {
            nb_move = 0;
            element = move_snake(struct_grid, &snake);
            /* If the snake eat a fruit it becomes longer */
            if (element == FRUIT) {
                nb_fruit = nb_fruit - 1;
                add_segment(&snake, get_x_last_snake_part(snake), get_y_last_snake_part(snake));
                /* End the game and display a message on the window */
                if (nb_fruit == 0){
                    MLV_clear_window(MLV_COLOR_BLACK);
                    MLV_draw_text(height/3, width/3, "Vous avez réussi a manger tous les fruits, victoire !", MLV_COLOR_RED);
                    MLV_actualise_window();
                    sleep(5);
                    break;
                }
            }
            /* If the snake touches a wall or a snake the game is over */
            else if (element == WALL || element == SNAKE) {
                break;
            }
        }
        /* Actualise the game window with the updated grid */
        draw_grid(struct_grid);
        MLV_actualise_window();
        /* Change the direction of the snake with the Arrow keyboard */
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
    /* Close the game  window and remove the allocation of the snake and grid in the memory */
    MLV_free_window();
    free_snake(&snake);
    free_grid(struct_grid);
    return 0;
}
