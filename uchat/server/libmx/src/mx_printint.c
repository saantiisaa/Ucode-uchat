#include "../inc/libmx.h"
void mx_printint(int n) {
    if(n < 0) {
        if(n == -2147483648) {
            write(1,"-2147483648",11);
            return;
        }
        n*=-1;
        write(1,"-",1);
    }
    if(n==2147483647) {
        write(1,"2147483647",10);
    }else if(n == 0){
        write(1,"0",1);
    }else{
    int rev_n=0;
    for(;n!=0;) {
        rev_n*=10;
        rev_n+=n%10;
        n=n/10;
    }
    for(;rev_n!=0;) {
        char c = (rev_n % 10)+48;
        write(1,&c,1);
        rev_n=rev_n/10;
    }
    }
}

