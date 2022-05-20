#include<stdio.h>
#include<ctype.h>

void upper_string(char *chaine){
    int i;
    for(i = 0; *(chaine+i) != '\0'; i++){
        *(chaine+i) = toupper(*(chaine+i));
    }
}


int main(int argc, char* argv[]){
    int i;
    printf("%d\n", argc);
    for(i = 0; i < argc; i++){
        upper_string(argv[i]);
        printf("%s\n",argv[i]);
    }
    return 0;
}