#include<stdio.h>

void f(int * tab)
{
    printf("%li\n",sizeof(tab));
}
int main()
{
    int tab[10];
    f(tab);
    return 0;
}