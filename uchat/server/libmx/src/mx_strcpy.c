#include "../inc/libmx.h"

char *mx_strcpy(char *dst, char *src) {
    int i = 0;
    for (; *src; i++)
     *dst++ = *src++;

    for (; *dst; i++)
     *dst++ = 0;

    dst -= i;
    return dst;
}

