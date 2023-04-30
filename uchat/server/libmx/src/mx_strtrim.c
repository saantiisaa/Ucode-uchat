#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if(str==NULL)
        return NULL;
    //int c=0;
    while (mx_isspace(*str)){ 
        str++;
    }
    int c=0;
    for(int i = mx_strlen(str)-1; i >= 0; i--) {
        if(mx_isspace(str[i])) {
            c++;
        }else {
            break;
        }
    }

    return mx_strndup(str, mx_strlen(str) - c);
}

/*int main(){
    char *str = "\f My name is Neo     \n\f";
    printf("%s\n",mx_strtrim(str));
}*/


