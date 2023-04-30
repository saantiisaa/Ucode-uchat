#include "../inc/libmx.h"
void mx_del_arr(char **arr) {
    for (int i = 0; arr[i] != NULL; i++){
		mx_strdel(&arr[i]);
    }
}
