#include "../inc/libmx.h"

char *mx_itoa(int number){
       char *result = NULL;
    bool is_neg =false;
    int c =0;
    if (number == 0) {
        result = mx_strnew(1);
        result[0] = '0';
        return result;
    }
    if(number < 0) {
        if(number == -2147483648) {
            return "-2147483648";
        }
        number*=-1;
        is_neg = true;
        c++;
    }
    if(number==2147483647) {
        return "2147483647";
    }
    int t=number;
    for(;t!=0;) {
     //   rev_n*=10;
      //  rev_n+=number%10;
        t=t/10;
        c++;
    }

    if(is_neg){
        result = mx_strnew(c);
        result[0] = '-';
    }else{
        result = mx_strnew(c);
    }

    while ((number != 0 && c >= 0) && result[c] != '-') {
        result[--c] = (number % 10) + '0';
        number /= 10;
    }
    
    return result;
}

//int main(){
//    mx_printstr(mx_itoa(2147483647));
//}
