#include "../inc/libmx.h"

char **mx_strsplit(char const *s, char c) {
    if (s == NULL)
        return NULL;
    int size=mx_count_words(s,c);
    char **arr=malloc((size + 1)* sizeof(char *));
    int p=0;
    for(int i=0; s[i]&&s[i]!='\0'; i++) {
        if(s[i]!=c) {
            int j=i;
            while(s[j]!=c&&s[j]!='\0'){
                j++;
            }
            //char*w=mx_strnew(j-i);
            arr[p]=mx_strndup(&s[i], j - i);
            //mx_strdel(&w);
           p++;
           i=j;
        }
    }
    arr[size]=NULL;
    return arr;
}

/*int main(){
    char *str = "    My   name is   Neo    ";
    char ** arr = mx_strsplit(str,' ');
    for(int i = 0; i < mx_count_words(str,' '); i++){
        printf("%s\n",arr[i]);
    }
    
}*/
