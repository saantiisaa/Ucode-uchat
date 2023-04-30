#include "../inc/libmx.h"
void mx_pop_front(t_list **head) {
    if (*head == NULL || head == NULL) 
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    t_list *l = (*head)->next;
    //t_list *t = l->next;
    free(*head); 
    *head = l;
}

