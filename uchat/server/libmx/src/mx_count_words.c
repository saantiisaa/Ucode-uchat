#include "../inc/libmx.h"

int mx_count_words(const char *str,char delimiter) {
    int c = 0;
    int t = 1;
    //if(str[0]==delimiter)c--;
    for(int i=0; str[i]!='\0'; i++) {
        if(str[i]==delimiter) {
            t = 1;
        }else if (t)
        {
            t = 0;
            c++;
        }
        
    }
    return c;
}

/*int main(){
    char* str = "  follow *   the  white rabbit ";
    printf("%d\n",mx_count_words(str,'*'));
    printf("%d\n",mx_count_words(str,' '));
}*/

