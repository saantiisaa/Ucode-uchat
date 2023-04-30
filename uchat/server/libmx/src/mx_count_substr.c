#include "../inc/libmx.h"


int mx_count_substr(const char *str,const char *sub) {
    if(str == NULL || sub == NULL)
        return -1;
    int c=0;
    while (*str) {
        if (str == mx_strchr(str, sub[0])) {
            if (mx_strncmp(str, sub, mx_strlen(sub)) == 0) {
                c++;
            }
        }
        str++;
    }
    return c;
}
//*//*
