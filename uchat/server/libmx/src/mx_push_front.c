#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
    t_list *l = mx_create_node(data);
    l->next =*list;
    *list = l;
}


