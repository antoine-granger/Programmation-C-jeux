#include<stdio.h>


void scanf_matrice(int matrice[][2], int nb_ligne, int nb_colonne){
	int i, j;
	for(i = 0; i < nb_ligne; i++){
		for(j = 0; j < nb_colonne; j++){
			scanf("%d", &matrice[i][j]);
		}
	}
}


void affiche_matrice(int matrice[][2], int nb_ligne, int nb_colonne){
	int i,j;
	for(i = 0; i < nb_ligne; i++){
		for(j = 0; j < nb_colonne; j++){
			printf("%d", matrice[i][j]);
		}
		printf("\n");
	}
}



int sum_prod_matrice(int matrice[][2], int nb_ligne, int nb_colonne){
	int i,j,sum,result;
	result = 1;
	for(i = 0; i < nb_ligne; i++){
		sum = 0;
		for(j = 0; j < nb_colonne; j++){
			sum = sum + matrice[i][j];	
		}
		result = result*sum;
	}
	return result;
}


void debug(char matrice[][4], int nb_ligne, int nb_colonne){
	int i,j;
	for(i = 0; i < nb_ligne; i++){
		for(j = 0; j < nb_colonne; j++){
			printf("%c ", matrice[i][j]);
		}
		printf("\n");
	}
}


int main(){
	int result_sum_prod;
	int matrice[2][2];
	char matrice_char[4][4] = {{'r', 'r', 'r', 'r'}, {'v', 'v', 'v', 'v'}, {'b', 'b', 'b', 'b'}, {'r', 'r', 'r', 'r'}};
	scanf_matrice(matrice, 2, 2);
	printf("scanf tab : \n");
	affiche_matrice(matrice, 2, 2);
	result_sum_prod = sum_prod_matrice(matrice, 2, 2);
	printf("\nsomme et produits des lignes : %d", result_sum_prod);
	printf("\naffiche matrice de char :  \n");
	debug(matrice_char, 4, 4);
	return 0;
}
