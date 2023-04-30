#include "../inc/libmx.h"

int mx_strlen(const char *s) {
    int size=0;
    //int i=0;
    while(s[size]!=0) {
        size++;
        //i++;
    }
    return size;
}

