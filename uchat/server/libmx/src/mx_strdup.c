#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    char *str2 = malloc(mx_strlen(str) + 1);
    mx_strcpy(str2,(char *)str);
    return str2;
}

