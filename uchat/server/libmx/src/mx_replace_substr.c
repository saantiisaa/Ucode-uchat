#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (sub==NULL || str==NULL || replace==NULL)
        return NULL;

    int t =mx_count_substr(str, sub);
    //printf("%d\n",mx_strlen(str));
    int s = mx_strlen(str) - (t *mx_strlen(sub)) + (t * mx_strlen(replace));
    char *result = mx_strnew(s);
    char *copy = mx_strdup(str);
    int k = 0;
    for (int i = 0; i < s; i++) {
        int index = mx_get_substr_index(copy, sub);
        if (i != index) {
            result[k] = str[i];
            k++;
        }
        else if (i == index) {
            for (int j = 0; j < mx_strlen(replace); j++) {
                copy[j + i] = replace[j];
                result[k] = replace[j];
                k++;
            }
        }
    }
    return result;
}
/*
int main(){
    char *str = "My name is Neo";
    printf("%s\n",mx_replace_substr(str," ","__"));
}*/
