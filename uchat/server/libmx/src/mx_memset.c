#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *str = (char*)b;
    for (size_t i = 0; i < len; i++)
        str[i] = c;
    return b;
}

/*int main(){
    char *str = "My name is Neo";
    printf("%s\n",mx_memset(str,'1',10));
}*/

