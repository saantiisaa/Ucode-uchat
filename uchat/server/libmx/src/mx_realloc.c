#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    size_t len;

    if (ptr == 0)
	    return malloc(size);
    
    len = sizeof(ptr);
    if (size <= len){
	    return ptr;
    }
    void *res = malloc(size);
    mx_memcpy(res, ptr, len);
    free(ptr);
    return res;
}

