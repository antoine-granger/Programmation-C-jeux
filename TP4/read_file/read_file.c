#include<stdio.h>

#define MAX_LINE_SIZE 60

int main(){
    FILE* file;
    char line[MAX_LINE_SIZE] = "";
    file = fopen("toto.txt", "r+");
    if (file != NULL){
        while (fscanf(file, "%c", line) != EOF) {
            printf("%s", line);
        }
        fclose(file);
    }
    return 0;
}