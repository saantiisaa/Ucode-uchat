#include "../inc/libmx.h"
void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL)
        return;
    t_list *l = *head;
    //t_list *t;
    if (l->next == NULL) {
        free(l);
        l = NULL;
        return;
    } 
    while(l->next->next != NULL) {
        //t = l;
        l = l->next;
    }
    free(l->next); 
    l->next = NULL;
}


