#include "../inc/libmx.h"

int mx_sqrt(int x) {
    for(int i=0; i<x; i++) {
        if(x==i*i) {
            return i;
        }
    }
    return 0;
}

