#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    int size=0;
    int j=0;
    while(s[j]) {
        size++;
        j++;
    }
    for(int i=0; i < size/2; i++) {
        char t=s[size-i-1];
        s[size-i-1]=s[i];
        s[i]=t;
    }
}

