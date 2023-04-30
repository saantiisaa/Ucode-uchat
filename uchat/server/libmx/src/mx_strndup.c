#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *res = mx_strnew(n);

    for (int i = 0; i < (int)n; i++) {
        res[i] = s1[i];
    }
    res[n] = '\0';
    return res;
}//*//*

