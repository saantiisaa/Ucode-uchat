#include "../inc/libmx.h"
int mx_list_size(t_list *list) {
    //t_list *l = list;
    int count = 0;
    while(list->next != NULL) {
        list = list->next;
        count++;
    } 
    return count;
}

