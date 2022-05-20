#include<stdio.h>

int max_tab(int *tab, int taille){
	int save_max = 0;
	int i;
	for(i = 0; i < taille; i++){
		if(save_max < *(tab+i)){
			save_max = *(tab+i);
		}
	}
	return save_max;
}


void copy_tab1_in_tab2(int *tab1, int taille_tab1, int *tab2, int taille_tab2){
	int taille = taille_tab1;
	int i = 0;
	if(taille_tab1 > taille_tab2){
		taille = taille_tab2;
	}
	for(i = 0; i < taille; i++){
		*(tab2+i) = *(tab1+i); 
	}
}


void copy_tab2_in_tab1_tab3_in_tab1(int *tab1, int taille_tab1, int *tab2, int taille_tab2, int *tab3, int taille_tab3){
	copy_tab1_in_tab2(tab2, taille_tab2, tab1, taille_tab1);
	copy_tab1_in_tab2(tab3, taille_tab3, tab1, taille_tab1);
}


int get_size_string(char *string){
	int taille;
	for(taille = 0; *(string+taille) != '\0'; taille++){}
	return taille;
}


int compare_pref(char *string1, char *string2){
	int taille_string1;
	int taille_string2;
	int taille;
	int i;
	taille_string1 = get_size_string(string1);
	taille_string2 = get_size_string(string2);
	taille = taille_string2;	
	if(taille_string1 < taille_string2){
		taille = taille_string1;
	}
	for(i=0; (*(string1+i)==*(string2+i)) && (i < taille); i++){}
	return i;
}


int main(){
	int i;
	int tab1[] = {1,2,3};
	int tab2[] = {4,5,6,7};
	int tab3[] = {8,9};
	char string1[] = "maman";
	char string2[] = "mama_fat";
	int taille_string;
	int taille_common_pref;
	int taille_tab1 = 3;
	int taille_tab2 = 4;
	int taille_tab3 = 2;
	int max_in_tab = 0;
	max_in_tab = max_tab(tab1, taille_tab1);
	printf("max_tab() : %d", max_in_tab);
	copy_tab1_in_tab2(tab1, taille_tab1, tab2, taille_tab2);
	printf("\ncopy tab1 in tab2 : ");
	for(i = 0; i < taille_tab2; i++){
		printf("%d ", *(tab2+i));
	}
	copy_tab2_in_tab1_tab3_in_tab1(tab1, taille_tab1, tab2, taille_tab2, tab3, taille_tab3);
	printf("\ncopy tab2 in tab1 and tab3 in tab1 : ");
	for(i = 0; i < taille_tab1; i++){
		printf("%d ", *(tab1+i));
	}
	taille_string = get_size_string(string1);
	printf("\nget size of tab string : %d",taille_string);
	taille_common_pref = compare_pref(string1, string2);
	printf("\nget size common pref : %d", taille_common_pref);
	return 0;
}

