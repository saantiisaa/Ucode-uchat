#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL)
        return NULL;
    int c = 0;
    char* s = mx_strtrim(str);
    char* s2 = mx_strnew(mx_strlen(s));

    
    for (int i = 0; i < mx_strlen(s); i++) {
        if (mx_isspace(s[i])) {
            if(mx_isspace(s[i + 1]))
                continue;
        }
        s2[c] = s[i];
        c++;
    }
    return s2;
}

/*int main(){
    char *str = "\f My    name   is  Neo     \n\f";
    printf("%s\n",mx_del_extra_spaces(str));
}*/
