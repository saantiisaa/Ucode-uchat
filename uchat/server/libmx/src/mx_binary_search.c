#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (!arr)
        return -1;
    int min = 0;
    int max = size - 1;
    while (min <= max) {
        (*count)++;
        int mid = (min + max) / 2;
        if (mx_strcmp(arr[mid], s) == 0){
            return mid;
        }
        else if (mx_strcmp(arr[mid], s) < 0){
            min = mid + 1;
        }
        else if (mx_strcmp(arr[mid], s) > 0){
            max = mid - 1;
        }
    }
    *count = 0;
    return -1;
}

/*int main(){
    int c;
    char *arr[] = {"222","Abcd","aBc","ab","az","z"};
    int a = mx_binary_search(arr, 6, "az",&c);
    printf("index = %d count = %d\n", a, c);
}*/

