#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    while (*haystack) {
        if(mx_strncmp(haystack,needle,mx_strlen(needle))==0) {
            return (char *)haystack;
        }     
      haystack++;
    }
    return NULL;
}

/*int main(){
    char* str ="0123456789";
    char* sub ="8";
    printf("%s",mx_strstr(str,sub));
}*/


