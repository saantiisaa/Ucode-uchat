#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
    if(pow==0) {
        return 1;
    }
    double res=n;
    for(unsigned int i=0; i<pow-1; i++) {
        res*=n;
    }
    return res;
}

