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
    List plist = (List) malloc(sizeof(List));
    plist->v = data;
    plist->next = l;
    return  plist;
}


List remove_first(List l){
    List plist = (List) malloc(sizeof(List));
    plist = l->next;
    free(l);
    return plist;
}


int main(){
    int test, data;
    List plist = empty_list();
    List plist2 = empty_list();
    List plist3 = empty_list();
    data = 8;
    plist->v = 6;
    plist2->v = 2;
    plist->next = plist2;
    plist2->next = NULL;
    test = is_empty(plist);
    printf("%d\n", test);
    display_list_ite(plist);
    plist3 = add_first(data, plist);
    display_list_rec(plist3);
    plist3 = remove_first(plist3);
    display_list_rec(plist3);
    return 0;
}
