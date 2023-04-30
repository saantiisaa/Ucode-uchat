#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *str = (unsigned char *)s;

    for (size_t i = n; i > 0; i--) {
        if (*str == (unsigned char)c) {
            return str;
        }
        str++;
    }
    return NULL;
}

