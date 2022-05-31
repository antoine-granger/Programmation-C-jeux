#include<stdio.h>

#define MAX_LINE_SIZE 60

int main(){
    FILE *file;
    char line[MAX_LINE_SIZE] = "";
    file = fopen("toto.txt", "r+");
    if (file != NULL){
        while (fgets(line, MAX_LINE_SIZE, file) != NULL) {
            printf("%s", line);
        }
        fprintf(file, "\nbonjour");
        fclose(file);
    }
    return 0;
}