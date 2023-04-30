#include "../inc/libmx.h"

int mx_quicksort(char** arr, int left, int right){
    if (arr == NULL)
        return -1;
    
    static int c = 0;
    
    if (left < right) {        
        int j = left;
        for (int i = left; i < right; i++) {
            if (mx_strlen(arr[i]) < mx_strlen(arr[right])) {
                char *temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                j++;
            }
        }
        char *temp = arr[j];
        arr[j] = arr[right];
        arr[right] = temp;
        
        mx_quicksort(arr, left, j - 1);
        mx_quicksort(arr, j + 1, right);
        c++;
    }
    return c - 1;
}

/*int main(){
    char *arr[6] = {
        //"Michelangelo",
        //"Donatello",
        //"Leonardo",
        //"Raphael"
        "DCM",
        "Cleant Eastwood",
        "Dr Brown",
        "Einstein",
        "Jessica",
        "Biff Tannen"
    };
    printf("%d\n",mx_quicksort(arr,0,5));
    mx_print_strarr(arr,(const char *)"\n");
}
*/

