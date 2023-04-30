#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *t1 = (char *)src;
    char *t2 = (char *)dst;

    char *str = malloc(len);

    for (int i = 0; i < (int)len; i++){
        str[i] = t1[i];
    }
    for (int i = 0; i < (int)len; i++){
        t2[i] = str[i];
    }
    free(str);
    return dst;
}
/*
int main(){
    char *str = "My name is Neo";
    char *s =" ";
    mx_memmove(str,s,1);
    printf("%s\n",s);
}
*/

