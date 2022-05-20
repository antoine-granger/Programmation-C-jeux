#include <MLV/MLV_all.h>


int main(){
	/* Créé et affiche la fenêtre */
    int width_window = 640;
    int height_window  = 480;
    int coordonnee_x[3] = {213, 313, 413};
    int coordonnee_y[3] = {230, 150, 230};
	MLV_create_window( "beginner - 2 - shapes", "shapes", width_window, height_window );

    /* Dessine le ciel */
    MLV_draw_filled_rectangle(0, 0, width_window, height_window, MLV_COLOR_SKYBLUE);

    /* Dessine l'herbe */
    MLV_draw_filled_rectangle(0, height_window-100, width_window, 200, MLV_COLOR_GREEN2);

    /* Dessine la maison */
    MLV_draw_filled_rectangle(213, 230, 200, 150, MLV_COLOR_ORANGE3);

    /* Dessine le chemin devant la maison */
    MLV_draw_filled_rectangle(287, 380, 60, 100, MLV_COLOR_SADDLE_BROWN);

    /* Dessine les fenêtres de la maison */
    MLV_draw_filled_rectangle(213+200/6, 230+150/3, 40, 60, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(213+200/6*4, 230+150/3, 40, 60, MLV_COLOR_BLACK);

    /* Dessine la porte de la maison */
    MLV_draw_filled_rectangle(298, 280, 40, 100, MLV_COLOR_BLACK);

    /* Dessine le toit de la maison */
    MLV_draw_filled_polygon(coordonnee_x, coordonnee_y, 3, MLV_COLOR_DARKRED);

    MLV_actualise_window();
    /* Fermer la fenêtre */
    MLV_wait_seconds( 3);
	MLV_free_window();
	return 0;
}
