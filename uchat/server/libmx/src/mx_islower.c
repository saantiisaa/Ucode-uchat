#include "../inc/libmx.h"

bool mx_islower(int c) {
    if(c>96&&c<123) {
        return true;
    }
    else { 
        return false;
    }
}

