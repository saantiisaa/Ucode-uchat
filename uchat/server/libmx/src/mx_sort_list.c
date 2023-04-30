#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *, void *)) {
    if (list && cmp)
        for (t_list *l = list; l; l = l->next) {
            for (t_list *t = list; t->next; t = t->next) {
                if (cmp(t->data, t->next->data)) {
                    t_list *temp = t->data;
                    t->data = t->next->data;
                    t->next->data = temp;
                }
            }
        }
    return list;
}

