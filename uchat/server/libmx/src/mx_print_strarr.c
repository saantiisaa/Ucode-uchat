#include "../inc/libmx.h"

void mx_print_strarr(char **arr,const char* delim){
    if(arr == NULL || delim == NULL){
        return;
    }
    int counter = 0;
    while (arr[counter]!=NULL){
        mx_printstr(arr[counter]);
        mx_printchar(*delim);
        counter++;
    }
    mx_printchar('\n');
    
}

/*int main(){
    char*arr[5]={
        "arr",
        "kar",
        "karton",
        "makaron",
        NULL
    };
    //const char *a = "|";
    const char *b = NULL;
    mx_strarr(arr,b);
}*/
