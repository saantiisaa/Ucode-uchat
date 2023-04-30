#include "../inc/libmx.h"
void mx_push_back(t_list **list, void *data) {
    
    t_list *new = mx_create_node(data);
    if (*list == NULL) {
        *list = new;
        return;
    }
    t_list *l = *list;
    while(l->next != NULL) {
        l = l->next;
    }
    //t_list *new = mx_create_node(data);
    l->next = new;
}


