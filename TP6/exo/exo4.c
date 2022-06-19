#include<stdio.h>
#include<stdlib.h>

typedef struct _cell {
    int v;
    struct _cell * next;
}Cell;
typedef Cell * List;


enum Boolean{FALSE = 0, TRUE = 1};


void display_list_ite(List l){
    while(l != NULL)
    {
        printf("%d\n", l->v);
        l = l->next;
    }
}


void display_list_rec(List l){
    if(l != NULL)
    {
        printf("%d\n", l->v);
        display_list_rec(l->next);
    }
}


enum Boolean is_empty(List l){
    while(l != NULL)
    {
        if(l->v != 0){
            return FALSE;
        }
        l = l->next;
    }
    return TRUE;
}


List empty_list(){
    List plist = (List) malloc(sizeof(List));
    return plist;
}


List add_first(int data, List l){
    List plist = empty_list();
    plist->v = data;
    plist->next = l;
    return plist;
}


List remove_first(List l){
    List plist = empty_list();
    plist = l->next;
    free(l);
    return plist;
}


void free_list(List *l){
    List save_l;
    while(l[0] != NULL){
        save_l = l[0]->next;
        free(l[0]);
        l[0] = save_l;
    }
}


List get(int v, List * l){
    List save_l_0 = l[0];
    List save_l;
    while(l[0] != NULL){
        save_l = l[0]->next;
        if (l[0]->v == v){
            l[0]->v = 0;
            l[0] = save_l_0;
            return save_l;
        }
        l[0] = save_l;
    }
    return save_l_0;
}


int main(){
    List l = empty_list();
    List save_get_l;
    int i;
    for(i=5;i>0;i--)
        l = add_first(i, l);
    display_list_ite(l); /* affiche 1 2 3 4 5*/
    save_get_l = get(3, &l);
    display_list_ite(l); /* affiche 1 2 3 4 5*/
    free_list(&l);
    if(is_empty(l)) printf("la liste est vide\n");
    return 0;
}
