#include<stdio.h>


int main(int argc, char* argv[]){
    int i, res_sum, char_convert_int;
    res_sum = 0;
    for(i = 0; i < argc; i++){
        sscanf(argv[i],"%d",&char_convert_int);
        res_sum = res_sum + char_convert_int;
    }
    printf("%d\n",res_sum);
    return 0;
}
